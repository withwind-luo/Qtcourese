# 图标说明

图标来源：[google/material-design-icons](https://github.com/google/material-design-icons)（master 分支）。

- 风格：Material Icons **baseline（filled）**
- 尺寸：普通图标 48×48 PNG，`app_icon.png` 使用 2x 版本 96×96
- 颜色：黑色图形 + 透明背景
- 许可证：Apache License 2.0，见 `LICENSE-material-design-icons.txt`

## 文件与用途

| 文件 | Material 图标名 | 用途 |
|---|---|---|
| `new_file.png` | `editor/insert_drive_file` | 新建 |
| `open_file.png` | `file/folder_open` | 打开 |
| `save.png` | `content/save` | 保存 |
| `save_as.png` | `content/save_as` | 另存为 |
| `undo.png` | `content/undo` | 撤销 |
| `redo.png` | `content/redo` | 重做 |
| `cut.png` | `content/content_cut` | 剪切 |
| `copy.png` | `content/content_copy` | 复制 |
| `paste.png` | `content/content_paste` | 粘贴 |
| `select_all.png` | `content/select_all` | 全选 |
| `find.png` | `action/find_in_page` | 查找 |
| `replace.png` | `action/find_replace` | 替换 |
| `font_color.png` | `editor/format_color_text` | 字体颜色 |
| `font_size.png` | `editor/format_size` | 字体大小 |
| `background_color.png` | `editor/format_color_fill` | 背景颜色 |
| `line_numbers.png` | `editor/format_list_numbered` | 显示/隐藏行号 |
| `word_wrap.png` | `editor/wrap_text` | 自动换行 |
| `toolbar.png` | `action/view_headline` | 显示/隐藏工具栏 |
| `status_bar.png` | `action/view_agenda` | 显示/隐藏状态栏 |
| `settings.png` | `action/build` | 工具/设置（对应参考图的扳手） |
| `about.png` | `action/info` | 关于 |
| `app_icon.png` | `editor/edit_note` | 应用/窗口图标（96×96） |
| `autosave.png` | `action/schedule` | 定时自动保存（选做） |
| `exit.png` | `action/exit_to_app` | 退出 |
| `help.png` | `action/help` | 帮助 |

## 备选图标

| 文件 | Material 图标名 | 用途 |
|---|---|---|
| `palette.png` | `image/palette` | 背景颜色备选 |
| `view_compact.png` | `image/view_compact` | 状态栏图标备选 |
| `visibility.png` | `action/visibility` | 显示动作备选 |
| `visibility_off.png` | `action/visibility_off` | 隐藏动作备选 |

## 使用提示

- 图标为黑色，适合浅色工具栏；如果使用深色工具栏，可在同一仓库下载 `*_white_48dp.png` 版本。
- 仓库同时提供 outlined / round / sharp / twotone 风格，替换路径中的 `materialicons` 即可。
- 在 Qt Designer 中为 QAction 设置 icon 时可直接选择这些 PNG，或先把它们加入 `.qrc` 资源文件。
