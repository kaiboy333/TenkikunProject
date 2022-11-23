#include "SweepAndPrune.h"

SweepAndPrune::SweepAndPrune(std::vector<Collider*> colliders) : BlodePhase(colliders)
{
}

std::vector<std::pair<int, int>> SweepAndPrune::GetHitPairCollidersIndex()
{
    std::set<std::pair<float, int>> xline;

    //x軸の端点を追加
    for (auto i = 0, len = (int)rects.size(); i < len; i++) {
        auto& rect = rects[i];
        //左端を追加
        xline.insert(std::make_pair(rect.startX, i));
        //右端を追加
        xline.insert(std::make_pair(rect.startX + rect.width, i));
    }

    std::vector<std::pair<int, int>> hitPairIndexes;

    for (auto i = 0, len = (int)rects.size(); i < len; i++) {
        auto& rect = rects[i];

        //対象のRect(BoundingBox)の左端から始め、右端まで繰り返す
        auto startIter = xline.find(std::make_pair(rect.startX, i));
        auto endIter = xline.find(std::make_pair(rect.startX + rect.width, i));
        startIter++;
        for (auto& iter = startIter; iter != endIter; iter++) {
            auto pairSecondIndex = (*iter).second;
            //x軸で当たるのでペアにする
            auto& r1 = rects[i];
            auto& r2 = rects[pairSecondIndex];

            //y軸で当たるかチェック
            if (r1.startY <= r2.startY + r2.height && r1.startY + r1.height >= r2.startY) {
                //当たるならヒットするペアとして登録
                hitPairIndexes.push_back(std::make_pair(i, pairSecondIndex));
            }
        }
    }

    return hitPairIndexes;
}
