#ifndef IDCOUNTER_H
#define IDCOUNTER_H

typedef unsigned int ID;

/* For counting objects inside each derived class separate */
template<class T>
class IdCounterT
{
private:
    static inline ID objects_count = 1;

protected:
    ID id;

public:
    static void increaseId() { IdCounterT<T>::objects_count++; }

    IdCounterT(bool increase_id = true) {
        this->id = IdCounterT<T>::objects_count;
        if (increase_id) IdCounterT<T>::objects_count++;
    }

    ID getId() const {return this->id;}
};



/* For counting all objects within base and its derived classes */
class IdCounter
{
private:
    static inline ID objects_count = 1;

protected:
    ID id;

public:
    static void increaseId() { IdCounter::objects_count++; }

    IdCounter(bool increase_id = true) {
        this->id = IdCounter::objects_count;
        if (increase_id) IdCounter::objects_count++;
    }

    ID getId() const {return this->id;}
};

#endif // IDCOUNTER_H
