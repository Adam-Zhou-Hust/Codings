/**
 * 利用 C++ 实现单例模式
 * 只允许提供一个类的实例对象
 * 1.不考虑多线程下安全性
 * 2.考虑多线程下的安全性
 * 3.应当注意的一些细节，拷贝赋值，友元
 */
// 很显然，构造函数肯定是私有的，同时提供 static 方法返回 static 实例
// 1. 懒汉模式

class Single {
public:
	// 返回单例的成员函数
	static Single *getInstance() {
		return pInstance;
	}
private:
	Single() { }
	static Single *pInstance;
}

Single *
Single::pInstance = NULL;

Single *
Single::getInstance() {
	if (!pInstance) {
		pInstance = new Single();
	}
	return pInstance;
}

// 很显然，上述方法在请求对象时候才会创建对象，可以视为一种延迟，称懒汉模式
// 也可以先创建对象，在任何请求之前就创建对象，成为饿汉模式，但是带来了不必要的资源消耗
// 由于对象肯定占据资源，如果创建后很久都没有请求对象的需求，那么这些资源被白白浪费

// 2. 饿汉模式

class Single {
public:
	static Single *getInstance() {
		return pInstance;
	}
private:
	Single();
	static Single *pInstance;
}

Single *
Single::pInstance = new Single();

/**
 * 现在，我我们考虑线程安全性
 * 1. 在懒汉模式中，由于要检查条件 if (pInstance) ,如果此时被抢占，那么可能另一个线程会创建对象
 *    返回这个线程时候，又创建了一次，从而导致多个对象的出现，因此，不具备线程安全性
 * 2. 饿汉模式中，由于先就创建了对象，也不需要判断，因此是线程安全的，就是前期开销大一些
 */

// 针对以上讨论，懒汉模式的线程安全性如何保证呢？我们可以加锁，保证 pInstance 这个临界资源的独占性
// 方法一：直接加原始的互斥锁

class Single {
private:
	// 需要包含相关头文件
	static pthread_mutex_t mutex;
	static Single *pInstance;
	Single() {
		pthread_mutex_init(&mutex);
	}
public:
	// 不需要每一次判断之前都加锁，因为只要不是空，那么就不需要
	// 创建新对象，因此可以利用 双重检测 指针，来避免开销
	// 双重检测的必要性
	// 在第一次判断后，如果线程被别的线程抢占，可能会创建好对象
	// 返回这个线程后如果不判断，那么就又创建了新的对象，因此必须两次
	Single *getInstance() {
		if (pInstance == NULL) {
			pthread_mutex_lock(&mutex);
			if (pInstance == NULL) 
				pInstance = new Single();
			pthread_mutex_unlock(&mutex);
		}
		return pInstance;
	}
};

pthread_mutex_t 
Single::mutex;

Single * Single::pInstance = NULL;

// 由此，也保证了懒汉模式下的线程安全性
/**
 * 单例模式可以扩展为指定个数的多例模式
 * 让单例类拥有多个静态指针即可，具体可以自己实现
 */



// 除此之外，我们还可以自己封装一个锁，用于懒汉模式下的线程安全性保证
