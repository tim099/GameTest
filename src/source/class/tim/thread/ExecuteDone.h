#ifndef EXECUTEDONE_H_
#define EXECUTEDONE_H_
namespace Tim{
	class Thread;
}
namespace Tim{
class ExecuteDone {
public:
	ExecuteDone();
	virtual ~ExecuteDone();
	virtual void done(Tim::Thread* thread)=0;
};
} /* namespace Tim */
#endif /* EXECUTEDONE_H_ */
