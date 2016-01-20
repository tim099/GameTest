#ifndef SELECTABLE_H_
#define SELECTABLE_H_
class Mouse;
/*
 * this is just a selectable interface
 * inherit this and implement your self
 */
const int Selectable_null=0;
const int Selectable_on=1;
const int Selectable_selected=2;
class Selectable {
public:
	Selectable();
	virtual ~Selectable();
	/*
	 * define update behavior
	 */
	virtual void update();
	/*
	 * define behavior after mouse on this item
	 */
	virtual void mouse_on();
	/*
	 * define behavior after selected
	 */
	virtual void selected();
	/*
	 * return true if mouse collide with this object
	 */
	virtual bool detect_mouse_collision(Mouse *mou)=0;
	/*
	 * set the state
	 */
	void set_state(int state);
protected:
	int state;
};

#endif /* SELECTABLE_H_ */
