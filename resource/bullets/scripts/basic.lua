function iterate()
	pos = Bullet.getPos()
	vel = Bullet.getVel()
	
	Bullet.setPos(pos.x + 1 * msElapsed()/100, pos.y + 1 * msElapsed()/100)
end