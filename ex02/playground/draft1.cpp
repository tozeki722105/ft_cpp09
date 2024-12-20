// void insert(std::container<T> &dest_container, std::container<T> &second_vals_container)
// {
// n==1 なら、destcontainer[i]のpair.secondを先頭に挿入 (*)
//  2、2、6、10、22、42、...というヤコブスタール数列のサイズでグループを作成し
//  各サイズでsecond_vals_containerのvalをグループ分け
//  グループ内のindexが大きい順にバイナリサーチでの挿入ソートで値を入れていく
//  ex) {y2} {y4, y3,} -> {y6, y5,} -> {y12, y11, y10, y9, y8, y7,} -> {y22, y21…
//		y1　= (*)で挿入した x1のpair.second
// }

// #define REC_STOP_MIN_SIZE 2

// std::container<T> mis(std::container<T> &container)
// {
// if (container.size() <= REC_STOP_MIN_SIZE){
// 	sort(container);
// 	return std::container<T> container;
// }

// std::container<std::pair <T, T> >を作成
// Pairの値を降順に並び替え。これで、first >= second
// std::container<T> first_vals_container = extractPairFirstVal();
// std::container<T>　ret = mis(first_container);
// std::container<T> second_vals_container = extractPairSecondVal();
// retにPairのsecond側をinsert insert(ret, second_vals_container)
// return std::container<T> ret
// }
