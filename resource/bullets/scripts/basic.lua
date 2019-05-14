function iterate()
	vel = Bullet.getVel()
	pos = Bullet.getPos()
	
	pos.x = 50 * math.sin(Bullet.getLife()/300) + 50
	pos.y = 50 * math.cos(Bullet.getLife()/300) + 80
	
	Bullet.setVel(vel.x, vel.y)
	Bullet.setPos(pos.x + vel.x * msElapsed()/1000, pos.y + vel.y * msElapsed()/1000)
end