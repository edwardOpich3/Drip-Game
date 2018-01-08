#include "Collision.h"
#include <math.h>

bool Collision::isColliding(Collision other)
{
	if ((other.center - center).magnitude() > radius + other.radius)
	{
		if (!usesOBB)
		{
			return false;
		}
		else
		{
			// Implement SAT check here

			float thisRadius = radius;
			float otherRadius = other.radius;

			// First, get the local axes of both this box and the other box
			Vector2 localAxes[2];
			localAxes[0] = Vector2(objectToWorld * Vector3(1.0f, 0.0f, 0.0f));
			localAxes[1] = Vector2(objectToWorld * Vector3(0.0f, 1.0f, 0.0f));

			Vector2 otherAxes[2];
			otherAxes[0] = Vector2(other.objectToWorld * Vector3(1.0f, 0.0f, 0.0f));
			otherAxes[1] = Vector2(other.objectToWorld * Vector3(0.0f, 1.0f, 0.0f));

			// Matrix to convert to/from the two coordinate systems
			Matrix3 toModel;
			for (unsigned int i = 0; i < 2; i++)
			{
				for (unsigned int j = 0; j < 2; j++)
				{
					toModel[i][j] = localAxes[j].dot(otherAxes[j]);
				}
			}

			// Distance between the centers, rotated to our orientation
			Vector2 distance = other.center - center;
			distance[0] = distance.dot(localAxes[0]);
			distance[1] = distance.dot(localAxes[1]);

			Matrix3 absToModel;
			for (unsigned int i = 0; i < 2; i++)
			{
				for (unsigned int j = 0; j < 2; j++)
				{
					absToModel[i][j] = fabsf(toModel[i][j]);
				}
			}

			// This axes check (x, y)
			for (unsigned int i = 0; i < 2; i++)
			{
				thisRadius = getHalfWidth()[i];

				otherRadius = other.getHalfWidth()[0] * absToModel[i][0] + other.getHalfWidth()[1] * absToModel[i][1];

				if (fabsf(distance[i]) > fabsf(thisRadius + otherRadius))
				{
					return false;
				}
			}

			// Other axes check (x, y)
			for (unsigned int i = 0; i < 2; i++)
			{
				thisRadius = getHalfWidth()[0] * absToModel[0][i] + getHalfWidth()[1] * absToModel[1][i];

				otherRadius = other.getHalfWidth()[i];

				if (fabsf(distance[0] * absToModel[0][i] + distance[1] * absToModel[1][i]) > fabsf(thisRadius + otherRadius))
				{
					return false;
				}
			}
		}
	}

	return true;
}

Vector2 Collision::getHalfWidth()
{
	return max - center;
}

Collision& Collision::operator=(const Collision& other)
{
	radius = other.radius;

	usesOBB = other.usesOBB;

	center = other.center;
	min = other.min;
	max = other.max;

	orientation = other.orientation;
	objectToWorld = other.objectToWorld;

	return *this;
}

Collision::Collision()
{
}

Collision::Collision(const Collision& other)
{
	*this = other;
}

Collision::~Collision()
{
}
