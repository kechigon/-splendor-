#include "components.h"
#include<iostream>
#include<cstdio>
#include<time.h>
#include<stack>
#include<vector>
#include<queue>
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
	int jewelry_blue_num;
	int jewelry_green_num;
	int jewelry_gold_num;
	int card_white_num;
	int card_black_num;
	int card_red_num;
	int card_blue_num;
	int card_green_num;
	vector<CARD> reservation;
};

//最大プレイヤー数分のPLAYER構造体配列
PLAYER PLAYERS[4];

//プレイヤーの数
int PLAYER_NUM;

//シャッフル関数
inline void shuffle();

//ゲーム準備関数
inline void preparation();

//レンダリング関数
inline void rendering();

int main() {
	
	//プレイヤーの数を入力
	cout << "人数を入力してください(2～4):";
	cin >> PLAYER_NUM;

	//人数分構造体を作る
	for (int i = 0; i < PLAYER_NUM; i++) {
		PLAYERS[i] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	}
	PLAYERS[2].reservation =
	{
		{1, "W", 0, 1, 1, 1, 1},
	    {2, "Ba", 2, 0, 2, 2, 2},
	    {3, "R", 3, 3, 0, 3, 3},
	};
	PLAYERS[1].reservation =
	{
		{4, "Bu", 0, 0, 4, 0, 4},
	    {5, "Gr", 5, 5, 5, 5, 0},
	};
	PLAYERS[3].reservation =
	{
		{1, "W", 0, 1, 1, 1, 1},
		{2, "Ba", 2, 0, 2, 2, 2},
		{3, "R", 3, 3, 0, 3, 3},
	};

	//カードをシャッフル
	shuffle();

	//ゲーム準備
	preparation();

	rendering();
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


//レンダリング関数
inline void rendering() {

	/*t手持ちカードのレンダリングはレベル1のカードをレンダリングしている時まで各段に入る*/

	//宝石チップの数を表示
	printf("\n");
	printf("                                                                          ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		printf("________  ");
	}
	printf("\n");
	printf("                                                                          ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		if (PLAYERS[0].reservation[i].color == "W" || PLAYERS[0].reservation[i].color == "R") printf("|%d    %s|  ", PLAYERS[0].reservation[i].point, PLAYERS[0].reservation[i].color.c_str());
		else printf("|%d   %s|  ", PLAYERS[0].reservation[i].point, PLAYERS[0].reservation[i].color.c_str());
	}
	printf("\n");
	printf("                    W %d     Ba %d     R %d     Bu %d     Gr %d     Go %d", JEWELRY_WHITE, JEWELRY_BLACK, JEWELRY_RED, JEWELRY_BLUE, JEWELRY_GREEN, JEWELRY_GOLD);
	printf("       ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		printf("|      |  ");
	}
	printf("\n");

	//貴族カードを表示
	printf("                    ");
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		printf("_____  ");
	}
	//プレイヤー1の手持ちカードの情報を取得
	vector<queue<string>> hand1_information(PLAYERS[0].reservation.size());
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		if (PLAYERS[0].reservation[i].cost_white > 0) {
			string white_information = "W " + to_string(PLAYERS[0].reservation[i].cost_white);
			hand1_information[i].push(white_information);
		}
		if (PLAYERS[0].reservation[i].cost_black > 0) {
			string black_information = "Ba" + to_string(PLAYERS[0].reservation[i].cost_black);
			hand1_information[i].push(black_information);
		}
		if (PLAYERS[0].reservation[i].cost_red > 0) {
			string red_information = "R " + to_string(PLAYERS[0].reservation[i].cost_red);
			hand1_information[i].push(red_information);
		}
		if (PLAYERS[0].reservation[i].cost_blue > 0) {
			string blue_information = "Be" + to_string(PLAYERS[0].reservation[i].cost_blue);
			hand1_information[i].push(blue_information);
		}
		if (PLAYERS[0].reservation[i].cost_green > 0) {
			string green_information = "Gr" + to_string(PLAYERS[0].reservation[i].cost_green);
			hand1_information[i].push(green_information);
		}
	}
	printf("                   ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		if (hand1_information[i].size() == 4) {
			printf("|%s   |  ", hand1_information[i].front().c_str());
			hand1_information[i].pop();
		}
		else printf("|      |  ");
	}
	printf("\n");
	//場に出てる貴族カードの情報を取得
	vector<queue<string>> nobility_information(PLAYER_NUM + 1);
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		if (OPEN_NOBILITY[i].cost_white > 0) {
			string white_information = "W " + to_string(OPEN_NOBILITY[i].cost_white);
			nobility_information[i].push(white_information);
		}
		if (OPEN_NOBILITY[i].cost_black > 0) {
			string black_information = "Ba" + to_string(OPEN_NOBILITY[i].cost_black);
			nobility_information[i].push(black_information);
		}
		if (OPEN_NOBILITY[i].cost_red > 0) {
			string red_information = "R " + to_string(OPEN_NOBILITY[i].cost_red);
			nobility_information[i].push(red_information);
		}
		if (OPEN_NOBILITY[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(OPEN_NOBILITY[i].cost_blue);
			nobility_information[i].push(blue_information);
		}
		if (OPEN_NOBILITY[i].cost_green > 0) {
			string green_information = "Gr" + to_string(OPEN_NOBILITY[i].cost_green);
			nobility_information[i].push(green_information);
		}
	}
	printf("                    ");
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		if (nobility_information[i].size() == 3) {
			printf("|%s|  ", nobility_information[i].front().c_str());
			nobility_information[i].pop();
		}
		else printf("|   |  ");
	}
	printf("                   ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		if (hand1_information[i].size() == 3) {
			printf("|%s   |  ", hand1_information[i].front().c_str());
			hand1_information[i].pop();
		}
		else printf("|      |  ");
	}
	printf("\n");
	printf("                    ");
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		printf("|%s|  ", nobility_information[i].front().c_str());
		nobility_information[i].pop();
	}
	printf("                   ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		if (hand1_information[i].size() == 2) {
			printf("|%s   |  ", hand1_information[i].front().c_str());
			hand1_information[i].pop();
		}
		else printf("|      |  ");
	}
	printf("\n");
	printf("                    ");
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		printf("|%s|  ", nobility_information[i].front().c_str());
		nobility_information[i].pop();
	}
	printf("                   ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		printf("|%s   |  ", hand1_information[i].front().c_str());
		hand1_information[i].pop();
	}
	printf("\n");
	printf("                    ");
	for (int i = 0; i < PLAYER_NUM + 1; i++) {
		printf("-----  ");
	}
	printf("                   ");
	for (int i = 0; i < PLAYERS[0].reservation.size(); i++) {
		printf("--------  ");
	}
	printf("\n");

	//レベル3のカードを表示
	if (!DECK_LEVEL3.empty()) {
		printf("          ________   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		printf("________  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		printf("________  ");
	}
	printf("\n");
	if (!DECK_LEVEL3.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	//ポイントと色を表示
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		if (OPEN_LEVEL3[i].color == "W" || OPEN_LEVEL3[i].color == "R") printf("|%d    %s|  ", OPEN_LEVEL3[i].point, OPEN_LEVEL3[i].color.c_str());
		else printf("|%d   %s|  ", OPEN_LEVEL3[i].point, OPEN_LEVEL3[i].color.c_str());
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		if (PLAYERS[1].reservation[i].color == "W" || PLAYERS[1].reservation[i].color == "R") printf("|%d    %s|  ", PLAYERS[1].reservation[i].point, PLAYERS[1].reservation[i].color.c_str());
		else printf("|%d   %s|  ", PLAYERS[1].reservation[i].point, PLAYERS[1].reservation[i].color.c_str());
	}
	printf("\n");
	if (!DECK_LEVEL3.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		printf("|      |  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		printf("|      |  ");
	}
	printf("\n");
	//場に出てるレベル3のカードの情報を取得
	vector<queue<string>> card_level3_information(OPEN_LEVEL3.size());
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		if (OPEN_LEVEL3[i].cost_white > 0) {
			string white_information = "W " + to_string(OPEN_LEVEL3[i].cost_white);
			card_level3_information[i].push(white_information);
		}
		if (OPEN_LEVEL3[i].cost_black > 0) {
			string black_information = "Ba" + to_string(OPEN_LEVEL3[i].cost_black);
			card_level3_information[i].push(black_information);
		}
		if (OPEN_LEVEL3[i].cost_red > 0) {
			string red_information = "R " + to_string(OPEN_LEVEL3[i].cost_red);
			card_level3_information[i].push(red_information);
		}
		if (OPEN_LEVEL3[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(OPEN_LEVEL3[i].cost_blue);
			card_level3_information[i].push(blue_information);
		}
		if (OPEN_LEVEL3[i].cost_green > 0) {
			string green_information = "Gr" + to_string(OPEN_LEVEL3[i].cost_green);
			card_level3_information[i].push(green_information);
		}
	}
	if (!DECK_LEVEL3.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		if (card_level3_information[i].size() == 4) {
			printf("|%s   |  ", card_level3_information[i].front().c_str());
			card_level3_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	//プレイヤー2の手持ちカードの情報を取得
	vector<queue<string>> hand2_information(PLAYERS[1].reservation.size());
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		if (PLAYERS[1].reservation[i].cost_white > 0) {
			string white_information = "W " + to_string(PLAYERS[1].reservation[i].cost_white);
			hand2_information[i].push(white_information);
		}
		if (PLAYERS[1].reservation[i].cost_black > 0) {
			string black_information = "Ba" + to_string(PLAYERS[1].reservation[i].cost_black);
			hand2_information[i].push(black_information);
		}
		if (PLAYERS[1].reservation[i].cost_red > 0) {
			string red_information = "R " + to_string(PLAYERS[1].reservation[i].cost_red);
			hand2_information[i].push(red_information);
		}
		if (PLAYERS[1].reservation[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(PLAYERS[1].reservation[i].cost_blue);
			hand2_information[i].push(blue_information);
		}
		if (PLAYERS[1].reservation[i].cost_green > 0) {
			string green_information = "Gr" + to_string(PLAYERS[1].reservation[i].cost_green);
			hand2_information[i].push(green_information);
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		if (hand2_information[i].size() == 4) {
			printf("|%s   |  ", hand2_information[i].front().c_str());
			hand2_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL3.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		if (card_level3_information[i].size() == 3) {
			printf("|%s   |  ", card_level3_information[i].front().c_str());
			card_level3_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		if (hand2_information[i].size() == 3) {
			printf("|%s   |  ", hand2_information[i].front().c_str());
			hand2_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL3.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		if (card_level3_information[i].size() == 2) {
			printf("|%s   |  ", card_level3_information[i].front().c_str());
			card_level3_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		if (hand2_information[i].size() == 2) {
			printf("|%s   |  ", hand2_information[i].front().c_str());
			hand2_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL3.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		printf("|%s   |  ", card_level3_information[i].front().c_str());
		card_level3_information[i].pop();
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		printf("|%s   |  ", hand2_information[i].front().c_str());
		hand2_information[i].pop();
	}
	printf("\n");
	if (!DECK_LEVEL3.empty()) {
		printf("          --------   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL3.size(); i++) {
		printf("--------  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[1].reservation.size(); i++) {
		printf("--------  ");
	}
	printf("\n");

	//レベル2のカードを表示
	if (!DECK_LEVEL2.empty()) {
		printf("          ________   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		printf("________  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		printf("________  ");
	}
	printf("\n");
	if (!DECK_LEVEL2.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	//ポイントと色を表示
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		if (OPEN_LEVEL2[i].color == "W" || OPEN_LEVEL2[i].color == "R") printf("|%d    %s|  ", OPEN_LEVEL2[i].point, OPEN_LEVEL2[i].color.c_str());
		else printf("|%d   %s|  ", OPEN_LEVEL2[i].point, OPEN_LEVEL2[i].color.c_str());
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		if (PLAYERS[2].reservation[i].color == "W" || PLAYERS[2].reservation[i].color == "R") printf("|%d    %s|  ", PLAYERS[2].reservation[i].point, PLAYERS[2].reservation[i].color.c_str());
		else printf("|%d   %s|  ", PLAYERS[2].reservation[i].point, PLAYERS[2].reservation[i].color.c_str());
	}
	printf("\n");
	if (!DECK_LEVEL2.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		printf("|      |  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		printf("|      |  ");
	}
	printf("\n");
	if (!DECK_LEVEL2.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		printf("|      |  ");
	}
	//プレイヤー3の手持ちカードの情報を取得
	vector<queue<string>> hand3_information(PLAYERS[2].reservation.size());
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		if (PLAYERS[2].reservation[i].cost_white > 0) {
			string white_information = "W " + to_string(PLAYERS[2].reservation[i].cost_white);
			hand3_information[i].push(white_information);
		}
		if (PLAYERS[2].reservation[i].cost_black > 0) {
			string black_information = "Ba" + to_string(PLAYERS[2].reservation[i].cost_black);
			hand3_information[i].push(black_information);
		}
		if (PLAYERS[2].reservation[i].cost_red > 0) {
			string red_information = "R " + to_string(PLAYERS[2].reservation[i].cost_red);
			hand3_information[i].push(red_information);
		}
		if (PLAYERS[2].reservation[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(PLAYERS[2].reservation[i].cost_blue);
			hand3_information[i].push(blue_information);
		}
		if (PLAYERS[2].reservation[i].cost_green > 0) {
			string green_information = "Gr" + to_string(PLAYERS[2].reservation[i].cost_green);
			hand3_information[i].push(green_information);
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		if (hand3_information[i].size() == 4) {
			printf("|%s   |  ", hand3_information[i].front().c_str());
			hand3_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	//場に出てるレベル2のカードの情報を取得
	vector<queue<string>> card_level2_information(OPEN_LEVEL2.size());
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		if (OPEN_LEVEL2[i].cost_white > 0) {
			string white_information = "W " + to_string(OPEN_LEVEL2[i].cost_white);
			card_level2_information[i].push(white_information);
		}
		if (OPEN_LEVEL2[i].cost_black > 0) {
			string black_information = "Ba" + to_string(OPEN_LEVEL2[i].cost_black);
			card_level2_information[i].push(black_information);
		}
		if (OPEN_LEVEL2[i].cost_red > 0) {
			string red_information = "R " + to_string(OPEN_LEVEL2[i].cost_red);
			card_level2_information[i].push(red_information);
		}
		if (OPEN_LEVEL2[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(OPEN_LEVEL2[i].cost_blue);
			card_level2_information[i].push(blue_information);
		}
		if (OPEN_LEVEL2[i].cost_green > 0) {
			string green_information = "Gr" + to_string(OPEN_LEVEL2[i].cost_green);
			card_level2_information[i].push(green_information);
		}
	}
	if (!DECK_LEVEL2.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		if (card_level2_information[i].size() == 3) {
			printf("|%s   |  ", card_level2_information[i].front().c_str());
			card_level2_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		if (hand3_information[i].size() == 3) {
			printf("|%s   |  ", hand3_information[i].front().c_str());
			hand3_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL2.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		if (card_level2_information[i].size() == 2) {
			printf("|%s   |  ", card_level2_information[i].front().c_str());
			card_level2_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		if (hand3_information[i].size() == 2) {
			printf("|%s   |  ", hand3_information[i].front().c_str());
			hand3_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL2.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		printf("|%s   |  ", card_level2_information[i].front().c_str());
		card_level2_information[i].pop();
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		printf("|%s   |  ", hand3_information[i].front().c_str());
		hand3_information[i].pop();
	}
	printf("\n");
	if (!DECK_LEVEL2.empty()) {
		printf("          --------   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL2.size(); i++) {
		printf("--------  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[2].reservation.size(); i++) {
		printf("--------  ");
	}
	printf("\n");

	//レベル1のカードを表示
	if (!DECK_LEVEL1.empty()) {
		printf("          ________   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		printf("________  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		printf("________  ");
	}
	printf("\n");
	if (!DECK_LEVEL1.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	//ポイントと色を表示
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		if (OPEN_LEVEL1[i].color == "W" || OPEN_LEVEL1[i].color == "R") printf("|%d    %s|  ", OPEN_LEVEL1[i].point, OPEN_LEVEL1[i].color.c_str());
		else printf("|%d   %s|  ", OPEN_LEVEL1[i].point, OPEN_LEVEL1[i].color.c_str());
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		if (PLAYERS[3].reservation[i].color == "W" || PLAYERS[3].reservation[i].color == "R") printf("|%d    %s|  ", PLAYERS[3].reservation[i].point, PLAYERS[3].reservation[i].color.c_str());
		else printf("|%d   %s|  ", PLAYERS[3].reservation[i].point, PLAYERS[3].reservation[i].color.c_str());
	}
	printf("\n");
	if (!DECK_LEVEL1.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		printf("|      |  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		printf("|      |  ");
	}
	printf("\n");
	//場に出てるレベル1のカードの情報を取得
	vector<queue<string>> card_level1_information(OPEN_LEVEL1.size());
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		if (OPEN_LEVEL1[i].cost_white > 0) {
			string white_information = "W " + to_string(OPEN_LEVEL1[i].cost_white);
			card_level1_information[i].push(white_information);
		}
		if (OPEN_LEVEL1[i].cost_black > 0) {
			string black_information = "Ba" + to_string(OPEN_LEVEL1[i].cost_black);
			card_level1_information[i].push(black_information);
		}
		if (OPEN_LEVEL1[i].cost_red > 0) {
			string red_information = "R " + to_string(OPEN_LEVEL1[i].cost_red);
			card_level1_information[i].push(red_information);
		}
		if (OPEN_LEVEL1[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(OPEN_LEVEL1[i].cost_blue);
			card_level1_information[i].push(blue_information);
		}
		if (OPEN_LEVEL1[i].cost_green > 0) {
			string green_information = "Gr" + to_string(OPEN_LEVEL1[i].cost_green);
			card_level1_information[i].push(green_information);
		}
	}
	if (!DECK_LEVEL1.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		if (card_level1_information[i].size() == 4) {
			printf("|%s   |  ", card_level1_information[i].front().c_str());
			card_level1_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	//プレイヤー4の手持ちカードの情報を取得
	vector<queue<string>> hand4_information(PLAYERS[3].reservation.size());
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		if (PLAYERS[3].reservation[i].cost_white > 0) {
			string white_information = "W " + to_string(PLAYERS[3].reservation[i].cost_white);
			hand4_information[i].push(white_information);
		}
		if (PLAYERS[3].reservation[i].cost_black > 0) {
			string black_information = "Ba" + to_string(PLAYERS[3].reservation[i].cost_black);
			hand4_information[i].push(black_information);
		}
		if (PLAYERS[3].reservation[i].cost_red > 0) {
			string red_information = "R " + to_string(PLAYERS[3].reservation[i].cost_red);
			hand4_information[i].push(red_information);
		}
		if (PLAYERS[3].reservation[i].cost_blue > 0) {
			string blue_information = "Bu" + to_string(PLAYERS[3].reservation[i].cost_blue);
			hand4_information[i].push(blue_information);
		}
		if (PLAYERS[3].reservation[i].cost_green > 0) {
			string green_information = "Gr" + to_string(PLAYERS[3].reservation[i].cost_green);
			hand4_information[i].push(green_information);
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		if (hand4_information[i].size() == 4) {
			printf("|%s   |  ", hand4_information[i].front().c_str());
			hand4_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL1.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		if (card_level1_information[i].size() == 3) {
			printf("|%s   |  ", card_level1_information[i].front().c_str());
			card_level1_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		if (hand4_information[i].size() == 3) {
			printf("|%s   |  ", hand4_information[i].front().c_str());
			hand4_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL1.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		if (card_level1_information[i].size() == 2) {
			printf("|%s   |  ", card_level1_information[i].front().c_str());
			card_level1_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		if (hand4_information[i].size() == 2) {
			printf("|%s   |  ", hand4_information[i].front().c_str());
			hand4_information[i].pop();
		}
		else {
			printf("|      |  ");
		}
	}
	printf("\n");
	if (!DECK_LEVEL1.empty()) {
		printf("          |      |   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		printf("|%s   |  ", card_level1_information[i].front().c_str());
		card_level1_information[i].pop();
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		printf("|%s   |  ", hand4_information[i].front().c_str());
		hand4_information[i].pop();
	}
	printf("\n");
	if (!DECK_LEVEL1.empty()) {
		printf("          --------   ");
	}
	else {
		printf("                     ");
	}
	for (int i = 0; i < OPEN_LEVEL1.size(); i++) {
		printf("--------  ");
	}
	printf("             ");
	for (int i = 0; i < PLAYERS[3].reservation.size(); i++) {
		printf("--------  ");
	}
	printf("\n");
	printf("\n");

	//プレイヤー情報を表示
	printf("          ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		if(PLAYERS[i].point >= 10) printf("player%d %d                          ", i + 1, PLAYERS[i].point);
		else printf("player%d %d                           ", i + 1, PLAYERS[i].point);
	}
	printf("\n");
	printf("          ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		printf("chip: W%d  Ba%d  R%d  Bu%d  Gr%d  Go%d    ", PLAYERS[i].jewelry_white_num, PLAYERS[i].jewelry_black_num, PLAYERS[i].jewelry_red_num, PLAYERS[i].jewelry_blue_num, PLAYERS[i].jewelry_green_num, PLAYERS[i].jewelry_gold_num);
	}
	printf("\n");
	printf("          ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		printf("card: W%d  Ba%d  R%d  Bu%d  Gr%d         ", PLAYERS[i].card_white_num, PLAYERS[i].card_black_num, PLAYERS[i].card_red_num, PLAYERS[i].card_blue_num, PLAYERS[i].card_green_num);
	}
	printf("\n");
}