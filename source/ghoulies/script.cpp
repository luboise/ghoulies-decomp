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
      case kEndScript:
        operations.emplace_back(EndScriptOperation {});
        break;
      default:
        if (operation_size <= 8) {
          operations.emplace_back(
              RawScriptOperation {.opcode = opcode, .operand_bytes = {}});
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

          operations.emplace_back(RawScriptOperation {
              .opcode = opcode, .operand_bytes = operand_bytes});
        }
        break;
    }

    curr += operation_size;

    if (curr > asset.descriptor.size()) {
      throw std::runtime_error("Script opcodes have overrun descriptor.");
    }
  } while (opcode != kEndScript);

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
    status = this->Advance(ctx);
  } while (status == kOpHandled);

  return status != ScriptUpdateStatus::kError;
}

template<typename... Ts>
struct Overload : Ts...
{
  using Ts::operator()...;
};

ScriptUpdateStatus Script::Advance(GameContext& ctx)
{
  // TODO: Make this debug only
  if (this->current_operation_ > this->operations_.size()) {
    return ScriptUpdateStatus::kError;
  }

  if (this->current_operation_ == this->operations_.size()) {
    return ScriptUpdateStatus::kScriptEnded;
  }

  const ScriptOperation& current_op {this->operations_[current_operation_]};
  const auto visitor = Overload {
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

      [this](const SetBackgroundOperation& op) -> ScriptUpdateStatus
      {
        std::cout << "Setting background to " << op.background_aid.data()
                  << "\n";
        current_operation_++;
        return ScriptUpdateStatus::kOpHandled;
      },

      [this](const auto& /*other*/) -> ScriptUpdateStatus
      {
        current_operation_++;
        return ScriptUpdateStatus::kOpHandled;
      },
  };

  ScriptUpdateStatus return_status {std::visit(visitor, current_op)};
  return return_status;
};

}  // namespace ghoulies
