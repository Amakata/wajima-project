--io.output("test.txt");
--for i=1,10,1 do
--	io.write(i)
--	wdcon:print (1.1)
--	wdcon:print (1)
--	wdcon:print ("\n")	
--	wdcon:print ("vvv")
--	wdcon:print ("日本語")
--end
--io.close();

wdcon = zefiro.tolua.wdcon:new ()
keyinput = zefiro.tolua.KeyInput:new ()
mouseinput = zefiro.tolua.MouseInput:new ()
graphics = zefiro.tolua.Graphics:new ()
graphics:create ( 800 , 600 )
test = graphics:loadSprite("test.png")
test3 = graphics:loadSprite("test3.png")
x , y = 0 , 0
timer = zefiro.std.FSPTimer:new ()
timer:setFSP(24)
while not zefiro.tolua.isQuit() do
	zefiro.tolua.pumpMessage (true)
	if keyinput:getState() == true then
		-- エスケープキー(終了)
		if keyinput:isPress(1) == true then
			break
		end
	end
	if mouseinput:getState() == true then
		x = mouseinput:getX() 
		y = mouseinput:getY()
	end
	if not timer:isSkip() then 
		graphics:clear ()
		graphics:bltSinY( test , 0 , 0 , 20 , 100)
		graphics:bltAlpha( test , x-300 , y-200 )
		graphics:bltAlpha( test3 , 50 , 400 )
		graphics:bltText( x .. y   , 5 , 0 , 0 , 52 , 418 )
		graphics:bltText( string.format("座標(x,y) %d:%d FSP %d",x,y, timer:getRealFSP() )   , 5 , 0 , 0 , 52 , 402 )
		graphics:present ()
	end
	timer:wait()
end

