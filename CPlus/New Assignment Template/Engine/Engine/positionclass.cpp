////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"
#include <math.h>
#include "inputclass.h"
PositionClass::PositionClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed   = 0.0f;
	m_backwardSpeed  = 0.0f;
	m_upwardSpeed    = 0.0f;
	m_downwardSpeed  = 0.0f;
	m_leftTurnSpeed  = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed    = 0.0f;
	m_lookDownSpeed  = 0.0f;
	m_strafeLeftSpeed = 0.0f;
	m_strafeRightSpeed = 0.0f;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}


void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


void PositionClass::MoveForward(bool keydown)
{
	float radians;
	float zRadian;


	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if(m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if(m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;
	zRadian = m_rotationX * 0.0174532925f;
	// Update the position.
	m_positionX += sinf(radians) * cosf(zRadian) * m_forwardSpeed;
	m_positionY -= sin(zRadian) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;
	CaptureCamera();
	return;
}


void PositionClass::MoveBackward(bool keydown)
{
	float radians;
	float zRadian;

	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if(m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;
		
		if(m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;
	zRadian = m_rotationX * 0.0174532925f;
	// Update the position.
	m_positionX -= sinf(radians) * cosf(zRadian) * m_backwardSpeed;
	m_positionY += sin(zRadian) * m_backwardSpeed;
	m_positionZ -= cosf(radians) * m_backwardSpeed;

	CaptureCamera();
	return;
}


void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if(m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if(m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upwardSpeed;
	CaptureCamera();
	return;
}


void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if(m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downwardSpeed;
	CaptureCamera();
	return;
}


void PositionClass::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if(m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 0.005f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}


void PositionClass::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if(m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 0.005f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}
	return;
}


void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if(m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 0.005f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;
	// Keep the rotation maximum 90 degrees.
	if(m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}

void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if(m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 0.005f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}
	m_lookDownSpeed;//Use the mouse delta to add to modify value
	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}

void PositionClass::StrafeLeft(bool keydown)
{
	float radians;
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_strafeLeftSpeed += m_frameTime * 0.003f;

		if (m_strafeLeftSpeed > (m_frameTime * 0.03f))
		{
			m_strafeLeftSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_strafeLeftSpeed -= m_frameTime * 0.002f;

		if (m_strafeLeftSpeed < 0.0f)
		{
			m_strafeLeftSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX -= cosf(radians) * m_strafeLeftSpeed;
	m_positionZ += sinf(radians) * m_strafeLeftSpeed;
	CaptureCamera();
	return;
}

void PositionClass::StrafeRight(bool keydown)
{
	float radians;
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_strafeRightSpeed += m_frameTime * 0.003f;

		if (m_strafeRightSpeed > (m_frameTime * 0.03f))
		{
			m_strafeRightSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_strafeRightSpeed -= m_frameTime * 0.002f;

		if (m_strafeRightSpeed < 0.0f)
		{
			m_strafeRightSpeed = 0.0f;
		}
	}

	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += cosf(radians) * m_strafeRightSpeed;
	m_positionZ -= sinf(radians) * m_strafeRightSpeed;
	CaptureCamera();
	return;
}

void PositionClass::CaptureCamera()
{
	float max = 30;
	float mag = sqrt((m_positionX*m_positionX) + (m_positionY*m_positionY) + (m_positionZ*m_positionZ));
	if (mag > max)
	{
		m_positionX = (m_positionX / mag)*max;
		m_positionY = (m_positionY / mag)*max;
		m_positionZ = (m_positionZ / mag)*max;
	}
}

void PositionClass::MouseInput(int xMousePos, int yMousePos)
{
	if (xMousePos < 0)
	{
		xMousePos = fabsf(xMousePos);

		m_leftTurnSpeed += xMousePos * 0.01f;

		if (m_leftTurnSpeed > (xMousePos * 0.005f))
		{
			m_leftTurnSpeed = xMousePos * 0.005f;
		}
		xMousePos += m_rightTurnSpeed;
	}
	else if (xMousePos >= 0)
	{
		m_rightTurnSpeed += xMousePos * 0.01f;

		if (m_rightTurnSpeed > (xMousePos * 0.005f))
		{
			m_rightTurnSpeed = xMousePos * 0.005f;
		}
		xMousePos += m_leftTurnSpeed;
	}

	if (yMousePos < 0)
	{
		yMousePos = fabsf(yMousePos);

		m_lookUpSpeed += yMousePos * 0.01f;

		if (m_lookUpSpeed > (yMousePos * 0.005f))
		{
			m_lookUpSpeed = yMousePos * 0.005f;
		}
		yMousePos += m_lookDownSpeed;
	}
	else if (yMousePos >= 0)
	{
		m_lookDownSpeed += yMousePos * 0.01f;

		if (m_lookDownSpeed > (yMousePos * 0.005f))
		{
			m_lookDownSpeed = yMousePos * 0.005f;
		}
		yMousePos += m_lookUpSpeed;
	}
}