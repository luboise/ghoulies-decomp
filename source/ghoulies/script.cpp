#include <cassert>
#include <iostream>

#include "script.hpp"

#include "script_ops.hpp"

namespace ghoulies
{

Script::Script(const Asset& asset)
{
  std::array<uint32_t, 2> values {};
  static_assert(sizeof(values) == 8);

  std::vector<ScriptOperation> operations;

  operations.reserve(200);

  if (asset.descriptor.size() < 8) {
    throw std::
          runtime_error(
              "Unable to create script from descriptor with a sise smaller "
              "than 8 " "bytes.");
  }

  std::uint32_t curr {0};

  std::uint32_t operation_size {std::get<0>(values)};
  ScriptOpcode opcode {std::get<1>(values)};

  do {
    std::memcpy(
        static_cast<void*>(&values), &asset.descriptor[curr], sizeof(values));

    operation_size = values[0];
    opcode = std::bit_cast<ScriptOpcode>(values[1]);

    switch (opcode) {
      case EndScript: {
        operations.emplace_back(std::in_place_type<EndScriptOperation>);
        break;
      }
      case SetBackground: {
        AssetAID bg_aid {};

        std::memcpy(
            bg_aid.data(), &asset.descriptor[curr + 8], sizeof(AssetAID));

        operations.emplace_back(SetBackgroundOperation {bg_aid});
      };
      default: {
        if (operation_size <= 8) {
          operations.emplace_back(std::in_place_type<RawScriptOperation>,
                                  opcode);
        } else {
          Bytes operand_bytes(operation_size - 8);
          if (static_cast<std::size_t>(curr) + operation_size
              > asset.descriptor.size())
          {
            throw std::runtime_error("Script opcodes have overrun descriptor.");
          }

          std::memcpy(operand_bytes.data(),
                      &asset.descriptor[static_cast<std::size_t>(curr) + 8],
                      operation_size - 8);

          std::cout << "Pushing back value with opcode " << opcode
                    << " and data of size " << operand_bytes.size() << ".\n";

          ScriptOperation new_operation {
              RawScriptOperation(opcode, operand_bytes)};

          operations.push_back(new_operation);
        }
        break;
      }
    }

    curr += operation_size;

    if (curr > asset.descriptor.size()) {
      throw std::runtime_error("Script opcodes have overrun descriptor.");
    }
  } while (opcode != EndScript);

  // TODO: Make this debug only
  for (const auto& operation : operations) {
    if (operation.valueless_by_exception()) {
      throw std::runtime_error("Valueless script operations in script.");
    }
  }

  this->operations_ = std::move(operations);
}

Script::Script(std::vector<ScriptOperation> operations)
    : operations_(std::move(operations))
{
}

bool Script::Update(GameContext& ctx)
{
  ScriptUpdateStatus status {ScriptUpdateStatus::kError};
  do {
    status = HandleOperation(ctx, this->CurrentOperation());

    // TODO: Make this debug only
    if (this->current_operation_ > this->operations_.size()) {
      return ScriptUpdateStatus::kError != 0U;
    }

    if (this->current_operation_ == this->operations_.size()) {
      return ScriptUpdateStatus::kScriptEnded != 0U;
    }

    const ScriptOperation& current_op {this->CurrentOperation()};
  } while (status == kOpHandled);

  return status != ScriptUpdateStatus::kError;
}

template<typename... Ts>
struct Overload : Ts...
{
  using Ts::operator()...;
};

[[nodiscard]] const ScriptOperation& Script::CurrentOperation() const
{
  assert(this->operations_.size() > 0);
  assert(this->current_operation_ < this->operations_.size());

  return operations_[this->current_operation_];
}

ScriptUpdateStatus Script::HandleOperation(GameContext& ctx,
                                           const ScriptOperation& op)
{
  static const auto kVisitor = Overload {
      [](const EndScriptOperation&) -> ScriptUpdateStatus
      { return ScriptUpdateStatus::kScriptEnded; },

      [&ctx, this](const WaitForMoveOnOperation&) -> ScriptUpdateStatus
      {
        if (ctx.move_on) {
          current_operation_++;
          return ScriptUpdateStatus::kOpHandled;
        }

        return ScriptUpdateStatus::kStalled;
      },

      [this, &ctx](const SetBackgroundOperation& op) -> ScriptUpdateStatus
      {
        ctx.background_model_aid = op.background_aid;

        current_operation_++;
        return ScriptUpdateStatus::kOpHandled;
      },

      [this](const auto& /*other*/) -> ScriptUpdateStatus
      {
        current_operation_++;
        return ScriptUpdateStatus::kOpHandled;
      },
  };

  ScriptUpdateStatus return_status {std::visit(kVisitor, op)};
  return return_status;
}

}  // namespace ghoulies
