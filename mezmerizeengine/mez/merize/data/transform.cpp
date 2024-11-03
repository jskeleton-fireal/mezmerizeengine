#include "transform.h"

void Transform::LookAt(Vector f_worldspace_position)
{
	Vector dif = m_Position - f_worldspace_position;
	m_Angles.LookAt(dif);
}
