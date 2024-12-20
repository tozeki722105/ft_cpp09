与えられた制約に基づいてプログラムを作成する必要があります。

• プログラム名は PmergeMe とします。
• プログラムは正の整数列を引数として受け取れるようにする必要があります。
• プログラムはマージ挿入ソートアルゴリズム（Ford-Johnson アルゴリズム）を使用して正の整数列をソートする必要があります。

• プログラムの実行中にエラーが発生した場合、標準エラー出力にエラーメッセージを表示する必要があります。

この演習を検証するために、コード内で少なくとも2つの異なるコンテナを使用する必要があります。プログラムは少なくとも3000個の異なる整数を処理できる必要があります。

ジェネリック関数を使用するのを避け、各コンテナに対してアルゴリズムを実装することを強くお勧めします。

標準出力に1行ずつ表示する必要がある情報に関する追加のガイドラインを以下に示します。

• 1行目には、明示的なテキストに続いて、ソートされていない正の整数列を表示する必要があります。
• 2行目には、明示的なテキストに続いて、ソートされた正の整数列を表示する必要があります。
• 3行目には、正の整数列のソートに使用した最初のコンテナを指定して、アルゴリズムで使用された時間を示す明示的なテキストを表示する必要があります。
• 最終行には、正の整数列のソートに使用した2番目のコンテナを指定して、アルゴリズムで使用された時間を示す明示的なテキストを表示する必要があります。

ソートの実行に使用された時間の表示形式は自由ですが、選択した精度は、使用した2つのコンテナの違いをはっきりと確認できるものでなければなりません。

標準的な使用例を以下に示します。

```
$> ./PmergeMe 3 5 9 7 4 Before: 35974
After: 34579
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us $> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before:  141 79 526 321 [...]
After:   79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
$> ./PmergeMe "-1" "2"
Error
$> # OSX USER:
$> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
[...]
$>
```

この例では、時間の表示は意図的に奇妙になっています。もちろん、ソート部分とデータ管理部分の両方を含む、すべての操作の実行に使用された時間を示す必要があります。

警告: 前の演習で使用したコンテナはここでは使用禁止です。

重複に関連するエラーの管理はお任せします。
