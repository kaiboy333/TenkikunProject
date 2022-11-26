#include "SweepAndPrune.h"
#include "Debug.h"

SweepAndPrune::SweepAndPrune(const std::vector<Collider*>& colliders) : BlodePhase(colliders)
{
}

std::vector<std::pair<int, int>> SweepAndPrune::GetHitPairCollidersIndex()
{
    std::set<std::pair<float, int>> xline;

    //x���̒[�_��ǉ�
    for (auto i = 0, len = (int)rects.size(); i < len; i++) {
        auto& rect = rects[i];
        //���[��ǉ�
        xline.insert(std::make_pair(rect.startX, i));
        //�E�[��ǉ�
        xline.insert(std::make_pair(rect.startX + rect.width, i));
    }

    std::vector<std::pair<int, int>> hitPairIndexes;

    for (auto i = 0, len = (int)rects.size(); i < len - 1; i++) {
        auto& rect = rects[i];

        //�Ώۂ�Rect(BoundingBox)�̍��[����n�߁A�E�[�܂ŌJ��Ԃ�
        auto startIter = xline.find(std::make_pair(rect.startX, i));
        auto endIter = xline.find(std::make_pair(rect.startX + rect.width, i));
        if (startIter != xline.end() && endIter != xline.end()) {
            for (auto& iter = ++startIter; iter != endIter; iter++) {
                auto pairSecondIndex = (*iter).second;
                //x���œ�����̂Ńy�A�ɂ���
                auto& r1 = rects[i];
                auto& r2 = rects[pairSecondIndex];

                //y���œ����邩�`�F�b�N
                if (r1.startY <= r2.startY + r2.height && r1.startY + r1.height >= r2.startY) {
                    //����ւ��Ⴂ�̃y�A���Ȃ����T��
                    bool isFind = false;
                    for (auto& hitPairIndex : hitPairIndexes) {
                        //����Ⴂ�̃y�A�Ȃ�
                        if (hitPairIndex.first == pairSecondIndex && hitPairIndex.second == i) {
                            isFind = true;
                            break;
                        }
                    }
                    //�܂��ǉ����ĂȂ��Ȃ�
                    if (!isFind) {
                        //������Ȃ�q�b�g����y�A�Ƃ��ēo�^
                        hitPairIndexes.push_back(std::make_pair(i, pairSecondIndex));
                    }
                }
            }
        }
    }

    return hitPairIndexes;
}
