shadowspeed = 8

function initialize()
	clearColor = {108.0/255, 156.0/255, 106.0/255}
	drawList = {}
	
	sx = 1
	sy = 0.6
	time = 0
end

square = {}
square.type = "tristrip"
square.color = {0, 1, 0}
square.verts = { 
	{-1,  2},
	{-1,  0},
	{ 1,  0},
	{ 1,  2}
}

ninegon = {}
ninegon.type = "tristrip"
ninegon.color = {0, 0.6, 0}
ninegon.verts = {}
c = 9
for i=1, c do
	iOverC = math.rad((i/c)*360)
	table.insert( ninegon.verts, {2+math.sin(iOverC), -2+math.cos(iOverC)} )
end

circle = {}
circle.type = "tristrip"
circle.color = {0, 0.8, 0}
circle.verts = {}
c = 90
for i=1, c do
	iOverC = math.rad((i/c)*360)
	table.insert( circle.verts, {-4.5+math.sin(iOverC)*1.5, 1.8+math.cos(iOverC)*1.5} )
end

function update()
	lasttime = time
	time = os.clock()
	delta = time - lasttime
	sx = sx - delta/shadowspeed
	if sx<-1 then sx=1 end
	drawList = {square, ninegon, circle}
	
	shadows = {}
	for _,shape in ipairs(drawList) do
		shadow = {}
		shadow.type = "tristrip"
		shadow.color = {0.3, 0.3, 0.3}
		shadow.verts = {}
		for _,v in ipairs( shape.verts ) do
			table.insert( shadow.verts, {v[1]-sx, v[2]-sy} )
		end
		table.insert( shadows, shadow )
	end
	
	for _,shadow in ipairs(shadows) do
		table.insert( drawList, shadow )
	end
end