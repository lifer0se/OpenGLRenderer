#ifndef ACTOR_CLASS_H
#define ACTOR_CLASS_H

#include "Object.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/fwd.hpp"

using namespace glm;

namespace OpenGLRenderer
{
	class Actor: public Object
	{

	public:
		Actor() {};

		vec3 GetPosition();
		vec3 GetForward();
		vec3 GetRight();
		vec3 GetUp();
		vec3 GetRotation();
		vec3 GetScale();

		void Translate(vec3 offset);
		void SetPosition(vec3 position);
		void SetForward(vec3 forward);
		void SetRight(vec3 right);
		void SetUp(vec3 up);
		void SetRotation(vec3 rotation);
		void SetScale(vec3 scale);

	private:
		vec3 m_Position { 0.0f, 0.0f, 0.0f };
		vec3 m_Forward { 0.0f, 0.0f, 1.0f };
		vec3 m_Right { 1.0f, 0.0f, 0.0f };
		vec3 m_Up { 0.0f, 1.0f, 0.0f };
		vec3 m_Rotation { 0.0f, 0.0f, 0.0f };
		vec3 m_Scale { 1.0f, 1.0f, 1.0f };
	};

    class ActorDispatcher
    {
     public:
        ActorDispatcher(std::shared_ptr<Actor> actor) : m_Actor(actor) {};

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            auto t = std::dynamic_pointer_cast<T>(m_Actor);
            if (!t)
                return false;

            func(t);
            return true;
        }

     private:
        std::shared_ptr<Actor> m_Actor;
    };
}

#endif
