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
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:ClearOptions()

  if (speachCounter == 0) then
    dialog:Say("Oi Fada")
    speachCounter = speachCounter + 1
  else
    dialog:Say("Hmm eu posso pegar a fada e por no inventario!!!")
  end
  
end

function interactWith()
  
end

function destroy()
end