#ifndef SELECTABLE_H_
#define SELECTABLE_H_

/*
 * this is just a selectable interface
 * inherit this and implement your self
 */
namespace Input{
class Mouse;
class Selectable {
public:
	const static int state_null=0;
	const static int state_on=1;
	const static int state_select=2;
	const static int state_selected=3;
	Selectable();
	virtual ~Selectable();
	/*
	 * define behavior after mouse on this item
	 */
	virtual void mouse_on(Mouse* mou);
	/*
	 * define behavior when object being select
	 */
	virtual void select(Mouse* mou);
	/*
	 * define behavior after selected
	 */
	virtual void selected(Mouse* mou);
	/*
	 * return true if mouse collide with this object
	 */
	virtual bool detect_mouse_collision(Mouse *mou)=0;
	/*
	 * set the state
	 */
	void set_state(int state,Mouse* mou);
	/*
	 * push current object into selectable control to detect collision with mouse
	 * need to do this per frame because order is important(object call this function earlier
	 * will detect in higher priority
	 */
	void detect_selection();

	void clear_state();

	int get_state()const;
protected:
	int state;
};
}
#endif /* SELECTABLE_H_ */
