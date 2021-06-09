#include<iostream>
#include<fstream>
#include "fraction.h"
#include "polynomial.h"
#include "generator.h"

#define NumOfQuestions 16

int main() {
    std::string input_data;
    {
        std::ifstream tex("./TeX/integration.tex");
        if (!tex) {
            std::cout << "ファイルを読み込めませんでした。やり直してください。" << std::endl;
            return 0;
        }

        // ヘッダー部分読み込み
        std::string data;
        for(int i = 0; i < 24; i++) {
            std::getline(tex, data);
            input_data += data + "\n";
        }
    }

    Generator g;
    // Q&A生成
    std::vector<std::vector<std::string>> Q_and_A;
    for(int i = 0; i < NumOfQuestions; i++) {
        Q_and_A.push_back(g.Q_and_A());
    }


    // 問題印刷
    for(int i = 0; i < NumOfQuestions; i++) {
        input_data += Q_and_A[i][0] + "\n\n";
    }

    input_data += "\\end{enumerate}\n"
                  "\\newpage\n"
                  "\n"
                  "次の積分をせよ。\n"
                  "\\begin{enumerate}\n"
                  "  \\renewcommand{\\labelenumi}{(\\roman{enumi})}\n";

    // 答え印刷
    for(int i = 0; i < NumOfQuestions; i++) {
        input_data += Q_and_A[i][1] + "\n\n";
    }

    input_data += "\\end{enumerate}\n"
                  "\n"
                  "\\end{document}";

    //書き込み
    {
        std::ofstream tex("./TeX/integration.tex");
        if (!tex) {
            std::cout << "ファイルを開けませんでした。やり直してください。" << std::endl;
            return 0;
        }
        tex << input_data;
    }
}