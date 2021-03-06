#include "line.h"
#include "math.h"
#include "conio2.h"
#include "const.h"

line::line(const point* start, const int* color)
{
	this->setStart(start);
	this->setColor(color);
}

void line::draw(int** img)
{
	if (this->start == this->end || this->start.y == this->end.y || this->start.x == this->end.x)
		this->drawStraightLine(img);
	else
		this->drawDiagonalLine(img);
}

void line::drawStraightLine(int** img)
{
	if (this->start == this->end)
		setPixel(this->start.y, this->start.x, this->color, img);
	else if (this->start.y == this->end.y)
		this->drawStraightLineOX(this->start, this->end, img);
	else if (this->start.x == this->end.x)
		this->drawStraightLineOY(this->start, this->end, img);
}

void line::drawDiagonalLine(int** img)
{
	if (absolute(this->start.y - this->end.y) > absolute(this->start.x - this->end.x))
		this->drawDiagonalLineOY(img);
	else if (absolute(this->start.y - this->end.y) < absolute(this->start.x - this->end.x))
		this->drawDiagonalLineOX(img);
	else
	{		if (this->start.y < this->end.y)
		{
			int y = this->start.y;
			if (this->start.x < this->end.x)
				for (int x = this->start.x; x <= this->end.x; x++, y++)
					this->setPixel(y, x, this->color, img);
			else
				for (int x = this->start.x; x >= this->end.x; x--, y++)
					this->setPixel(y, x, this->color, img);
		}
		else
		{
			int y = this->end.y;
			if (this->start.x < this->end.x)
				for (int x = this->end.x; x >= this->start.x; x--, y++)
					this->setPixel(y, x, this->color, img);
			else
				for (int x = this->end.x; x <= this->start.x; x++, y++)
					this->setPixel(y, x, this->color, img);
		}
	}
	
}

void line::drawDiagonalLineOY(int** img)
{
	int parts, partialLength;
	point end, start;
	start = this->start;
	parts = absolute(this->start.x - this->end.x) + 1;
	partialLength = absolute(this->start.y - this->end.y) / parts;
	if(this->start.y < this->end.y)
		for (int i = 0; i < parts; i++)
		{
			if (i != parts - 1)
				end = { start.x, start.y + partialLength};
			else
				end = this->end;
		this->drawStraightLineOY(start, end, img);
			if (this->start.x < this->end.x)
				start.x++;
			else if (this->start.x > this->end.x)
				start.x--;
			start.y += partialLength;
		}
	if (this->start.y > this->end.y)
		for (int i = 0; i < parts; i++)
		{
			if (i != parts - 1)
				end = { start.x, start.y - partialLength };
			else
				end = this->end;
			this->drawStraightLineOY(start, end, img);
			if (this->start.x < this->end.x)
				start.x++;
			else if (this->start.x > this->end.x)
				start.x--;
			start.y -= partialLength;
		}
}

void line::drawDiagonalLineOX(int** img)
{
	int parts, partialLength;
	point end, start;
	start = this->start;
	parts = absolute(this->start.y - this->end.y) + 1;
	partialLength = absolute(this->start.x - this->end.x) / parts;
	if (this->start.x < this->end.x)
		for (int i = 0; i < parts; i++)
		{
			if (i != parts - 1)
				end = { start.x + partialLength, start.y };
			else
				end = this->end;
		this->drawStraightLineOX(start, end, img);
			if (this->start.y < this->end.y)
				start.y++;
			else if (this->start.y > this->end.y)
				start.y--;
			start.x += partialLength;
		}
	if (this->start.x > this->end.x)
		for (int i = 0; i < parts; i++)
		{
			if (i != parts - 1)
				end = { start.x - partialLength, start.y };
			else
				end = this->end;
			this->drawStraightLineOX(start, end, img);
			if (this->start.y < this->end.y)
				start.y++;
			else if (this->start.y > this->end.y)
				start.y--;
			start.x -= partialLength;
		}
}

