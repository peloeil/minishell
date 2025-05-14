# minishell
## Makefile
`make`: バイナリ `minishell` を作成

`make lsp`: compile_commands.json を生成(include のエラー対策、定義ジャンプのため)

`make test`: 単体テスト実行

`.c` ファイルを作成するときは `SRCS` に、`.h` ファイルを作成するときは `INCLUDES` に追加するのを忘れないようにする。
