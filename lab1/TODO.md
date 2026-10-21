# 实验 1 待处理问题

> 记录当前已知、尚未修复的边界问题，后续逐项处理。

- [ ] **除数为 0**
  - 现象：`8 ÷ 0 =` 会显示 `inf`。
  - 原因：`calculation()` 的除法分支直接执行 `operand1 / operand2`，没有判断除数。
  - 待办：除数为 0 时给出错误提示（如"除数不能为 0"）并进入错误状态，可用 `calculation(bool *ok)` 的 `ok` 参数返回失败。

- [ ] **等号后的输入状态**
  - 现象：`2 + 3 =` 得到 5 后直接输入 `7`，再按运算符或 `=` 时，栈中残留的 `5` 会参与运算，导致结果错误。
  - 原因：按 `=` 后结果被压入 `operands`，但直接输入新数字时没有清空 `operands` / `opcodes`。
  - 待办：增加 `afterEquals` 标志。等号后输入数字时清空 `operands` 和 `opcodes`；等号后按运算符时则以当前结果继续运算。

- [ ] **清除功能不彻底**
  - 现象：按 `C`（`btnClearAll`）只清空了当前 `operand`，之前压栈的操作数和运算符仍残留。
  - 待办：`btnClearAllClicked()` 中同时清空 `operands`、`opcodes`、`opcode` 和 `operand`。
