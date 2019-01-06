#include "GridTile.h"

GridTile::GridTile() {
}

GridTile::GridTile(Pos pos, int type) {
	pos_ = pos;
	type_ = type;
}

Pos GridTile::GetPos() {
	return pos_;
}

int GridTile::GetType() {
	return type_;
}

void GridTile::SetNeighbors(std::vector<Pos> neighbors) {
	neighbors_ = neighbors;
}

std::vector<Pos> GridTile::GetNeighbors() {
	return neighbors_;
}
