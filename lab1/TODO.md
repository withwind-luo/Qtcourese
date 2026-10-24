# 实验 1 问题记录

> 记录已知问题的处理情况。

- [x] **除数为 0**
  - 现象：`8 ÷ 0 =` 会显示 `inf`。
  - 原因：`calculation()` 的除法分支直接执行 `operand1 / operand2`，没有判断除数。
  - 修复：除法前判断除数为 0，显示“除数不能为 0”并进入错误态；按数字键或 C / CE 可恢复。

- [x] **等号后的输入状态**
  - 现象：`2 + 3 =` 得到 5 后直接输入 `7`，再按运算符或 `=` 时，栈中残留的 `5` 会参与运算，导致结果错误。
  - 原因：按 `=` 后结果被压入 `operands`，但直接输入新数字时没有清空 `operands` / `opcodes`。
  - 修复：增加 `afterEquals` 标志。等号后输入数字/小数点会清空 `operands` 和 `opcodes`，开始新计算；等号后按运算符则以当前结果继续运算。

- [x] **清除功能不彻底**
  - 现象：`btnClearAllClicked()` 只清空部分状态，显示屏仍显示旧内容。
  - 修复：`btnClearAllClicked()` 调用 `resetState()` 清空 `operand`、`operands`、`opcodes`、`opcode` 并清空显示屏；CE 只清除当前输入。

- [x] **单目运算的边界值**
  - 修复：`1/x` 输入 0 时提示“除数不能为 0”；`²√x` 输入负数时提示“无效输入”；等号后按单目键会以显示的结果继续运算。

- [x] **连续运算符**
  - 现象：`2 + × 3 =` 会沿用先按的 `+`（得到 5），而不是替换为 `×`。
  - 修复：`btnBinaryOperatorClicked()` 在 `operand` 为空时替换 `opcodes` 栈顶运算符。

- [x] **CE 键行为错误**
  - 现象：`btnClear` 连接到 `btnNumClicked`，点击会把“CE”追加到显示屏。
  - 修复：新增 `btnClearEntryClicked()`，CE 只清除当前输入；Delete 键映射到 CE。

- [x] **键盘焦点**
  - 修复：`display` 设为只读并禁止获得焦点（`NoFocus`），键盘事件统一进入 `keyPressEvent`；按钮保留可聚焦行为。
