//
// Created by hannes on 03.02.18.
//

#include <opencv2/opencv.hpp>
#include "player.h"
#include "team.h"

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(argv[1], -1);

    if (img.empty())
        return -1;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");

    Team team1{"Los Krachos"};
    team1.AddPlayer(Player("Hannes", 9, Position::MITTELBLOCKER));
    team1.AddPlayer(Player("Michi", 6, Position::AUSSENANGREIFER));

    cv::FileStorage file_storage("/home/hannes/workspace/data.yaml", cv::FileStorage::WRITE);
    file_storage << "team" << team1;
    file_storage.release();

    return 0;
}
