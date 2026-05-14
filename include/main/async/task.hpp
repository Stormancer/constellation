#pragma once
#include <backend/primitives.hpp>

namespace Constellation
{
class ITaskSource;

	template<typename TResult>
	class Task
	{
        public:
          Task(ITaskSource *obj, uint16 token) : _obj(obj), _token(token)
        {
            
        }
        private:
          ITaskSource *_obj;
          uint16 _token;
	};
}