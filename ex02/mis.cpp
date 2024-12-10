
#include <iostream>
#include <utility>
#include <vector>

typedef std::vector<int> t_vi;
typedef std::vector<std::pair<int, int> > t_vpi;


void disp(const t_vi &vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
}

t_vpi makeVecPair(t_vi &vec)
{
	t_vpi vpi;
	std::pair<int, int> val;

	size_t len = vec.size() / 2;

	for (size_t i = 0; i < len;  )
	{
		vpi.push_back(std::make_pair(vec[i], vec[i + 1]));
	}
	if (vec.size() % 2 == 1)
	
}

int main()
{
	t_vi vec = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 7};
	disp(vec);
	t_vpi vec_pair = makeVecPair(vec);
	vec_pair.PairsDescending();
	
	t_vi vec2 = extractFirstvec();
	t_vpi vec_pair2 = makeVecPair(vec2);
	vec_pair2.PairsDescending();
	
	if (vec3.size() > MIN_SIZE)
		return ;
	t_vi vec3 = extractFirstvec();
	t_vpi vec_pair3 = makeVecPair(vec3);
	vec_pair3.PairsDescending();
	//ret =
	t_vi vec3_2 = extractSecondvec();
	inset(ret, vec3_2);


	if (vec3.size() > MIN_SIZE)
		return ;

	
	


	
}


void insert(std::container<T> &dest_container, std::container<T> &second_vals_container)
{
	//n==1 なら、destcontainer[i]のpair.secondを先頭に挿入 (*)
	// 2、2、6、10、22、42、...というヤコブスタール数列のサイズでグループを作成し
	// 各サイズでsecond_vals_containerのvalをグループ分け
	// グループ内のindexが大きい順にバイナリサーチでの挿入ソートで値を入れていく
	// ex) {y4, y3,} -> {y6, y5,} -> {y12, y11, y10, y9, y8, y7,} -> {y22, y21…
	//		y1　= (*)で挿入した x1のpair.second, y2 = (*)の前までx1だったy1のpair.first

}

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