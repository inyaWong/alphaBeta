/*
 * 文件名：main.cpp
 * 作者：inyaWong
 * 日期：2023-06-01
 * 功能：使用博弈树算法的人机对弈7×7棋盘五子棋游戏
 * IDE：Code::Blocks 20.03
 */
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int max_depth = 4; // 博弈树最大深度
int human_player;
int ai_player;
int my_board[7][7];

// 判断当前位置是否在棋盘范围内
bool is_valid_move(int row, int col)
{
    return (row >= 0 && row < 7 && col >= 0 && col < 7 && my_board[row][col] == 0);
}

// 判断游戏是否结束
bool is_game_over()
{
    // 判断横向是否有五棋子相连
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (my_board[i][j] != 0 && my_board[i][j] == my_board[i][j + 1] && my_board[i][j] == my_board[i][j + 2] && my_board[i][j] == my_board[i][j + 3] && my_board[i][j] == my_board[i][j + 4])
            {
                return true;
            }
        }
    }
    // 判断纵向是否有五棋子相连
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (my_board[i][j] != 0 && my_board[i][j] == my_board[i + 1][j] && my_board[i][j] == my_board[i + 2][j] && my_board[i][j] == my_board[i + 3][j] && my_board[i][j] == my_board[i + 4][j])
            {
                return true;
            }
        }
    }
    // 判断左上到右下斜向是否有五棋子相连
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (my_board[i][j] != 0 && my_board[i][j] == my_board[i + 1][j + 1] && my_board[i][j] == my_board[i + 2][j + 2] && my_board[i][j] == my_board[i + 3][j + 3] && my_board[i][j] == my_board[i + 4][j + 4])
            {
                return true;
            }
        }
    }
    // 判断右上到左下斜向是否有五棋子相连
    for (int i = 0; i < 2; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            if (my_board[i][j] != 0 && my_board[i][j] == my_board[i + 1][j - 1] && my_board[i][j] == my_board[i + 2][j - 2] && my_board[i][j] == my_board[i + 3][j - 3] && my_board[i][j] == my_board[i + 4][j - 4])
            {
                return true;
            }
        }
    }
    // 判断是否还有空位
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (my_board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

// 计算当前分数
int score_position(int player)
{
    int my_score = 0;       // 当前玩家的得分
    int opponent_score = 0; // 对手的得分

    // 水平方向
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int count_human = 0; // 连续棋子数，初始化为0
            int count_ai = 0;
            for (int k = 0; k < 5; k++) // 计算连续五个棋子的得分
            {
                if (my_board[i][j + k] == human_player)
                {
                    count_human++;
                    count_ai = 0;
                }
                else if (my_board[i][j + k] == ai_player)
                {
                    count_human = 0;
                    count_ai++;
                }

                if (count_human == 0)
                {
                    int temp_score = pow(10, count_ai); // 计算AI的得分
                    if (player == ai_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
                else if (count_ai == 0)
                {
                    int temp_score = pow(10, count_human); // 计算人的得分
                    if (player == human_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
            }
        }
    }

    // 垂直方向
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int count_human = 0;
            int count_ai = 0;
            for (int k = 0; k < 5; k++)
            {
                if (my_board[i + k][j] == human_player)
                {
                    count_human++;
                    count_ai = 0;
                }
                else if (my_board[i + k][j] == ai_player)
                {
                    count_human = 0;
                    count_ai++;
                }

                if (count_human == 0)
                {
                    int temp_score = pow(10, count_ai);
                    if (player == ai_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
                else if (count_ai == 0)
                {
                    int temp_score = pow(10, count_human);
                    if (player == human_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
            }
        }
    }

    // 对角线方向，主对角线
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int count_human = 0;
            int count_ai = 0;
            for (int k = 0; k < 5; k++)
            {
                if (my_board[i + k][j + k] == human_player)
                {
                    count_human++;
                    count_ai = 0;
                }
                else if (my_board[i + k][j + k] == ai_player)
                {
                    count_human = 0;
                    count_ai++;
                }

                if (count_human == 0)
                {
                    int temp_score = pow(10, count_ai);
                    if (player == ai_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
                else if (count_ai == 0)
                {
                    int temp_score = pow(10, count_human);
                    if (player == human_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
            }
        }
    }

    // 对角线方向，次对角线
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            int count_human = 0;
            int count_ai = 0;
            for (int k = 0; k < 5; k++)
            {
                if (my_board[i + k][j - k] == human_player)
                {
                    count_human++;
                    count_ai = 0;
                }
                else if (my_board[i + k][j - k] == ai_player)
                {
                    count_human = 0;
                    count_ai++;
                }

                if (count_human == 0)
                {
                    int temp_score = pow(10, count_ai);
                    if (player == ai_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
                else if (count_ai == 0)
                {
                    int temp_score = pow(10, count_human);
                    if (player == human_player)
                    {
                        my_score += temp_score;
                    }
                    else
                    {
                        opponent_score += temp_score;
                    }
                }
            }
        }
    }

    // 返回两者得分的差
    return my_score - opponent_score;
}

// 获取AI下一步的最佳行动
pair<int, pair<int, int>> alpha_beta(int depth, int player, int alpha, int beta)
{
    vector<pair<int, int>> valid_moves;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (is_valid_move(i, j))
            {
                valid_moves.push_back(make_pair(i, j));
            }
        }
    }

    int best_score;
    pair<int, int> best_move;
    if (valid_moves.empty() || depth == max_depth)
    {
        best_score = score_position(ai_player) - score_position(human_player);
        return make_pair(best_score, make_pair(-1, -1));
    }
    else if (player == ai_player)
    {
        best_score = -10000;
        for (auto move : valid_moves)
        {
            my_board[move.first][move.second] = ai_player;
            int score = alpha_beta(depth + 1, human_player, alpha, beta).first;
            my_board[move.first][move.second] = 0;
            if (score > best_score)
            {
                best_score = score;
                best_move = move;
            }
            alpha = max(alpha, best_score);
            if (beta <= alpha)
            {
                break; // beta 剪枝
            }
        }
        return make_pair(best_score, best_move);
    }
    else
    {
        best_score = 10000;
        for (auto move : valid_moves)
        {
            my_board[move.first][move.second] = human_player;
            int score = alpha_beta(depth + 1, ai_player, alpha, beta).first;
            my_board[move.first][move.second] = 0;
            if (score < best_score)
            {
                best_score = score;
                best_move = move;
            }
            beta = min(beta, best_score);
            if (beta <= alpha)
            {
                break; // alpha 剪枝
            }
        }
        return make_pair(best_score, best_move);
    }
}

pair<int, pair<int, int>> minimax(int depth, int player)
{
    return alpha_beta(depth, player, -10000, 10000); // 初始化
}
// 绘制井字棋盘
void print_board()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (my_board[i][j] == 0)
                cout << "| ";
            else if (my_board[i][j] == 1)
                cout << "|X";
            else
                cout << "|O";
        }
        cout << "|" << endl;
        cout << "+-+-+-+-+-+-+-+" << endl;
    }
}

int main()
{
    cout << "欢迎来到五子棋游戏！" << endl;
    cout << "请输入您想要使用的玩家类型（1-玩家先手，2-AI先手）：";
    cin >> human_player;
    ai_player = (human_player == 1) ? 2 : 1;

    while (true)
    {
        if (human_player == 1)
        {
            int row, col;
            cout << "请输入您下棋的位置（行列以空格分隔）：";
            cin >> row >> col;
            if (is_valid_move(row, col))
            {
                my_board[row][col] = human_player;
                print_board();
            }
            else
            {
                cout << "您输入的位置不合法，请重新输入。" << endl;
                continue;
            }

            if (is_game_over())
            {
                break;
            }
        }

        cout << "AI正在思考中......" << endl;
        pair<int, pair<int, int>> ai_move = minimax(0, ai_player);
        my_board[ai_move.second.first][ai_move.second.second] = ai_player;
        cout << "AI下了(" << ai_move.second.first << "," << ai_move.second.second << ")" << endl;
        print_board();

        if (is_game_over())
        {
            break;
        }

        if (human_player == 2)
        {
            int row, col;
            cout << "请输入您下棋的位置（行列以空格分隔）：";
            cin >> row >> col;
            if (is_valid_move(row, col))
            {
                my_board[row][col] = human_player;
                print_board();
            }
            else
            {
                cout << "您输入的位置不合法，请重新输入。" << endl;
                continue;
            }

            if (is_game_over())
            {
                break;
            }
        }
    }

    if (score_position(human_player) > score_position(ai_player))
    {
        cout << "恭喜您获得了胜利！" << endl;
    }
    else if (score_position(human_player) < score_position(ai_player))
    {
        cout << "很遗憾，您输了。" << endl;
    }
    else
    {
        cout << "游戏结束，双方战平。" << endl;
    }

    return 0;
}
