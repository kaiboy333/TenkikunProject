#include "Rect.h"
#include "Debug.h"
#include <typeinfo>
#include "TreeNode.h"

Rect::Rect(float startX, float startY, float width, float height)
{
	this->startX = startX;
	this->startY = startY;
	this->width = width;
	this->height = height;
}

void Rect::Draw()
{
}

bool Rect::IsPointIn(float x, float y)
{
	return startX <= x && startX + width >= x && startY <= y && startY + height >= y;
}

bool Rect::IsPointIn2(float x, float y)
{
	return startX <= x && startX + width > x && startY <= y && startY + height > y;
}

std::vector<Vector2> Rect::GetPoints()
{
	std::vector<Vector2> points;

	points.push_back(Vector2(startX, startY));
	points.push_back(Vector2(startX, startY + height));
	points.push_back(Vector2(startX + width, startY + height));
	points.push_back(Vector2(startX + width, startY));

	return points;
}

Rect* Rect::GetCrossRect(Rect* r1, Rect* r2)
{
	std::vector<Vector2> crossPoints;	//交点たち

	//四角の頂点がもう一方の四角内にあるならリストに追加
	for (Vector2 point : r1->GetPoints()) {
		if (r2->IsPointIn2(point.x, point.y)) {
			crossPoints.push_back(point);
		}
	}
	for (Vector2 point : r2->GetPoints()) {
		if (r1->IsPointIn2(point.x, point.y)) {
			crossPoints.push_back(point);
		}
	}

	std::vector<Vector2> points1 = r1->GetPoints();
	std::vector<Vector2> points2 = r2->GetPoints();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Vector2 p1 = points1[i % 4];
			Vector2 p2 = points1[(i + 1) % 4];
			Vector2 p3 = points2[j % 4];
			Vector2 p4 = points2[(j + 1) % 4];

			Vector2 crossPoint;

			//交点があるなら
			if (Vector2::IsCross(p1, p2, p3, p4, crossPoint)) {
				//リストに追加
				crossPoints.push_back(crossPoint);
			}
		}
	}

	//重ならなかったら
	if (crossPoints.size() == 0) {
		//無を返す
		return nullptr;
	}

	Vector2 minPoint = crossPoints[0], maxPoint = crossPoints[0];

	//頂点の左上と右下を探す
	for (Vector2 point : crossPoints) {
		if (point.x <= minPoint.x && point.y <= minPoint.y) {
			minPoint.x = point.x;
			minPoint.y = point.y;
		}
		if (point.x >= maxPoint.x && point.y >= maxPoint.y) {
			maxPoint.x = point.x;
			maxPoint.y = point.y;
		}
	}


	float width = maxPoint.x - minPoint.x;
	float height = maxPoint.y - minPoint.y;

	return new Rect(minPoint.x, minPoint.y, width, height);

}
