#include "components.h"
#include<iostream>
#include<cstdio>
#include<time.h>
#include<stack>
#include<set>
#include<vector>
using namespace std;

//山札
stack<CARD> DECK_LEVEL1, DECK_LEVEL2, DECK_LEVEL3;
stack<NOBILITY> DECK_NOBILITY;

//場に出てるカード
vector<CARD> OPEN_LEVEL1(4);
vector<CARD> OPEN_LEVEL2(4);
vector<CARD> OPEN_LEVEL3(4);
vector<NOBILITY> OPEN_NOBILITY;

//プレイヤーの構造体
struct PLAYER {
	int point;
	int jewelry_white_num;
	int jewelry_black_num;
	int jewelry_red_num;
	int jewelry_blud_num;
	int jewelry_green_num;
	int card_white_num;
	int card_black_num;
	int card_red_num;
	int card_blue_num;
	int card_green_num;
	set<CARD> reservation;
};

//プレイヤーの数
int PLAYER_NUM;

//シャッフル関数
inline void shuffle();

//ゲーム準備関数
inline void preparation();

int main() {
	
	//プレイヤーの数を入力
	cout << "人数を入力してください(2～4):";
	cin >> PLAYER_NUM;

	//人数分構造体を作る
	PLAYER players[4];
	for (int i = 0; i < PLAYER_NUM; i++) {
		players[i] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	}

	//カードをシャッフル
	shuffle();

	//ゲーム準備
	preparation();

	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		cout << OPEN_NOBILITY[i].cost_white << " ";
	}
	cout << "\n";

	for (int i = 0; i < 4; i++) {
		cout << OPEN_LEVEL1[i].color_num << " ";
	}
	cout << "\n";

	for (int i = 0; i < 4; i++) {
		cout << OPEN_LEVEL2[i].color_num << " ";
	}
	cout << "\n";

	for (int i = 0; i < 4; i++) {
		cout << OPEN_LEVEL3[i].color_num << " ";
	}
}

//シャッフル関数
inline void shuffle() {

	//ランダムな値を得るために初期値をsrandで初期化
	srand((unsigned int)time(NULL));

	/*フィッシャーイェーツのシャッフルでシャッフル*/

	//カードレベル1をシャッフル
	for (int i = 39; i > 0; i--) {
		
		//ランダムな値を取得
		int r = rand() % (i + 1);

		CARD tmp = CARD_LEVEL1[i];
		CARD_LEVEL1[i] = CARD_LEVEL1[r];
		CARD_LEVEL1[r] = tmp;
	}

	//山札にシャッフルした情報を入れる
	for (int i = 0; i < 40; i++) {
		DECK_LEVEL1.push(CARD_LEVEL1[i]);
	}

	//カードレベル2をシャッフル
	for (int i = 29; i > 0; i--) {

		//ランダムな値を取得
		int r = rand() % (i + 1);

		CARD tmp = CARD_LEVEL2[i];
		CARD_LEVEL2[i] = CARD_LEVEL2[r];
		CARD_LEVEL2[r] = tmp;
	}

	//山札にシャッフルした情報を入れる
	for (int i = 0; i < 30; i++) {
		DECK_LEVEL2.push(CARD_LEVEL2[i]);
	}

	//カードレベル3をシャッフル
	for (int i = 19; i > 0; i--) {

		//ランダムな値を取得
		int r = rand() % (i + 1);

		CARD tmp = CARD_LEVEL3[i];
		CARD_LEVEL3[i] = CARD_LEVEL3[r];
		CARD_LEVEL3[r] = tmp;
	}

	//山札にシャッフルした情報を入れる
	for (int i = 0; i < 20; i++) {
		DECK_LEVEL3.push(CARD_LEVEL3[i]);
	}

	//貴族カードをシャッフル
	for (int i = 8; i > 0; i--) {

		//ランダムな値を取得
		int r = rand() % (i + 1);

		NOBILITY tmp = CARD_NOBILITY[i];
		CARD_NOBILITY[i] = CARD_NOBILITY[r];
		CARD_NOBILITY[r] = tmp;
	}

	//山札にシャッフルした情報を入れる
	for (int i = 0; i < 9; i++) {
		DECK_NOBILITY.push(CARD_NOBILITY[i]);
	}
}

//ゲーム準備関数
inline void preparation() {
	
	//プレイヤーの数によってチップの数を決める
	if (PLAYER_NUM == 2) {
		JEWELRY_WHITE -= 3;
		JEWELRY_BLACK -= 3;
		JEWELRY_RED -= 3;
		JEWELRY_BLUE -= 3;
		JEWELRY_GREEN -= 3;
	}
	else if (PLAYER_NUM == 3) {
		JEWELRY_WHITE -= 2;
		JEWELRY_BLACK -= 2;
		JEWELRY_RED -= 2;
		JEWELRY_BLUE -= 2;
		JEWELRY_GREEN -= 2;
	}

	//プレイヤーの数によって貴族の数を決める
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		OPEN_NOBILITY.push_back(DECK_NOBILITY.top());
		DECK_NOBILITY.pop();
	}

	//最初に場に出すカードを決める
	for (int i = 0; i < 4; i++) {
		OPEN_LEVEL1[i] = DECK_LEVEL1.top();
		DECK_LEVEL1.pop();
		OPEN_LEVEL2[i] = DECK_LEVEL2.top();
		DECK_LEVEL2.pop();
		OPEN_LEVEL3[i] = DECK_LEVEL3.top();
		DECK_LEVEL3.pop();
	}
}
