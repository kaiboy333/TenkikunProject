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

std::vector<Vector3> Rect::GetPoints()
{
	std::vector<Vector3> points;

	points.push_back(Vector3(startX, startY, 0));
	points.push_back(Vector3(startX, startY + height, 0));
	points.push_back(Vector3(startX + width, startY + height, 0));
	points.push_back(Vector3(startX + width, startY, 0));

	return points;
}

float Rect::Cross(Vector3 a, Vector3 b)
{
	return a.x * b.y - a.y * b.x;
}


Rect* Rect::GetCrossRect(Rect* r1, Rect* r2)
{
	std::vector<Vector3> crossPoints;	//交点たち

	//四角の頂点がもう一方の四角内にあるならリストに追加
	for (Vector3 point : r1->GetPoints()) {
		if (r2->IsPointIn2(point.x, point.y)) {
			crossPoints.push_back(point);
		}
	}
	for (Vector3 point : r2->GetPoints()) {
		if (r1->IsPointIn2(point.x, point.y)) {
			crossPoints.push_back(point);
		}
	}

	std::vector<Vector3> points1 = r1->GetPoints();
	std::vector<Vector3> points2 = r2->GetPoints();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Vector3 p1 = points1[i % 4];
			Vector3 p2 = points1[(i + 1) % 4];
			Vector3 p3 = points2[j % 4];
			Vector3 p4 = points2[(j + 1) % 4];

			float det = Cross(p2 - p1, p4 - p3);

			//平行じゃないなら
			if (det != 0) {
				float s = Cross(p3 - p1, p4 - p3) / det;
				float t = Cross(p2 - p1, p1 - p3) / det;

				//線分の交点なら
				if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
					crossPoints.push_back(Vector3(p1.x + s * (p2 - p1).x, p1.y + s * (p2 - p1).y, 0));
				}
			}
		}
	}

	//重ならなかったら
	if (crossPoints.size() == 0) {
		//無を返す
		return nullptr;
	}

	Vector3 minPoint = crossPoints[0], maxPoint = crossPoints[0];

	//頂点の左上と右下を探す
	for (Vector3 point : crossPoints) {
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
