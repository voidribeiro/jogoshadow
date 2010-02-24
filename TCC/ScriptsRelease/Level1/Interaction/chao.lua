function start()
	print("Starting inventory manager")
end

function update()
end

function interact()
  walk()
end

function inspect()
  walk()
end

function walk()
  local selector = ComponentSelector.GetFrom(parentObject)
  local skeleton = ComponentSkeleton.GetFrom("player")

  local mouseX,mouseY = Game.GetMousePosition()
  
  local posX, posY, posZ = selector:GetCollisionPoint(mouseX, mouseY)
  print(posX, posY, posZ)
  
  skeleton:WalkTo(posX, posY, posZ)
end

function interactWith()
  
end

function destroy()
end