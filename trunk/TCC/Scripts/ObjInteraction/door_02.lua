local isInInvetory = 0

local co = nil

function start()
  isInInventory = Game.IsInInventory(parentObject)
end

function update()
  if not(co == nil) then
    coroutine.resume(co)
  end
end

function interact()
  if (isInInventory == 0) then
    local selector = ComponentSelector.GetFrom(parentObject)
    local skeleton = ComponentSkeleton.GetFrom("player")

    local mouseX,mouseY = Game.GetMousePosition()

    local posX, posY, posZ = selector:GetCollisionPoint(mouseX, mouseY)

    skeleton:WalkTo(posX, posY, posZ)
    
    co = coroutine.create(addToInventory);
  else
    print("interact da fada no inventário")
  end
end

function addToInventory()
  local skeleton = ComponentSkeleton.GetFrom("player")
  while not(skeleton:IsWalking() == 0) do
    coroutine.yield(co)
  end
  print("adicionou a fada no inventário")
  Game.AddToInventory(parentObject)
  isInInventory = 1
end


speachCounter = 0

function inspect()
  if (speachCounter == 0) then
    print("This is another nice door!!!")
    speachCounter = speachCounter + 1
  else
    print("No... this is not a door. It look like one but its an ugly farrie model!!!")
  end
  
end

function interactWith()
  
end

function destroy()
end