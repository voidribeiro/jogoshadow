function start()
	print("Starting inventory manager")
end

function update()
end

function interact()
  local selector = ComponentSelector.GetFrom(parentObject)
  local skeleton = ComponentSkeleton.GetFrom("player")

  local mouseX,mouseY = Game.GetMousePosition()
  
  local posX, posY, posZ = selector:GetCollisionPoint(mouseX, mouseY)
  print(posX, posY, posZ)
  
  skeleton:WalkTo(posX, posY, posZ)
  
end

function inspect()
  local dialog = ComponentDialog.GetFrom("dialogo")
  --dialog:ClearOptions()
  dialog:Say("Este eh o chao... ele eh Verde")

end

function interactWith()
  
end

function destroy()
end