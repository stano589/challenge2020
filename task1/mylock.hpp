#ifndef __MYLOCK_HPP__
#define __MYLOCK_HPP__

#include <mutex>

namespace Mylock{
	template<typename Lockable>
	class lock_guard{
		public:
			// we do not want implicit constructor
			explicit lock_guard(Lockable& _mtx) : mtx(_mtx) {
				mtx.lock();
			}
			
			lock_guard(Lockable& _mtx, std::adopt_lock_t) : mtx(_mtx) {

			}

			~lock_guard(){
				mtx.unlock();
			}
			// do not want any copies
			// delete assignment operator and copy constructor
			lock_guard(const lock_guard & right) = delete;
			lock_guard& operator=(const lock_guard& right) = delete;
		private:
			Lockable& mtx;
	};
}

#endif // __MYLOCK_HPP__