#ifndef SELECTABLE_H_
#define SELECTABLE_H_
class Mouse;
/*
 * this is just a selectable interface
 * inherit this and implement your self
 */
class Selectable {
public:
	Selectable();
	virtual ~Selectable();
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
private:

};

#endif /* SELECTABLE_H_ */
