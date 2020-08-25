#include "Slug.h"
#include "Character.h"
Slug::Slug(Direction direction, int x, int y, int speed, std::string fileName, int rows, int cols, int width, int height, int lives)
	: Enemy(direction, x, y, speed, fileName, rows, cols, width, height, lives)
{
	sheet = new SpriteSheet(fileName, rows, cols);
	anime = new Animation(-1, 8, 0, rows*cols - 1);
}
void Slug::randomMove(vector<Obstacle*>& obstacles, int enemy_width, int enemy_height)
{

}
void Slug::Move_to_character(Character &character)
{
	chase_degree = GetDegree(x, y, character.GetX(), character.GetY());
	chase_vector = new Vector(chase_degree, speed);
	x += round(chase_vector->getX());
	y += round(chase_vector->getY());
	chase_vector->setX(0);
	chase_vector->setY(0);
}

void Slug::Draw(Graphics & gfx)
{
	if (!death) {
		sheet->drawFrame(gfx, anime->getCurrentFrame(), x, y);
		anime->nextFrame();
	}

}
