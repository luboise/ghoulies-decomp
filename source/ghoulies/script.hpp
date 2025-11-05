#include <cstring>
#include <vector>

#include "bnl.hpp"
#include "game.hpp"
#include "script_ops.hpp"

namespace ghoulies
{

enum ScriptUpdateStatus
{
  kOpHandled,
  kStalled,
  kError,
  kScriptEnded
};

class Script
{
public:
  /// throws std::runtime_error on failure, initialises a script otherwise
  explicit Script(const Asset& asset);
  explicit Script(std::vector<ScriptOperation> operations);

  bool Update(GameContext& ctx);

  [[nodiscard]] const ScriptOperation& CurrentOperation() const;

private:
  ScriptUpdateStatus HandleOperation(GameContext& ctx,
                                     const ScriptOperation& op);

  std::vector<ScriptOperation> operations_;
  std::size_t current_operation_ {0};
};

}  // namespace ghoulies
