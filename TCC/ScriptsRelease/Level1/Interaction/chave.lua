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
    walk()
    co = coroutine.create(addToInventory);
  else
    print("AAAAAAAAAAAAAAAAAAAAAAAA interact!")
  end
end

function addToInventory()
  local skeleton = ComponentSkeleton.GetFrom("player")
  while not(skeleton:IsWalking() == 0) do
    coroutine.yield(co)
  end
  Game.AddToInventory(parentObject)
  isInInventory = 1
end

local speachCounter = 0

function inspect()
  if (isInInventory == 0) then
    walk()
  end
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:ClearOptions()

  if (speachCounter < 1) then
    dialog:Say("Uma chave num local improvavel. Quem diria.")
  else
    if (speachCounter < 2) then
      dialog:Say("Como eu pude perder tal item.")
    else
      if (speachCounter < 3) then
        dialog:Say("Bom... vou pegar a chave logo ou vou ficar enrolando?")
      else
        dialog:Say("Tudo bem. Tenho o dia inteiro para decidir.")
      end
    end
  end
  speachCounter = speachCounter + 1
end

function walk()
  local selector = ComponentSelector.GetFrom(parentObject)
  local skeleton = ComponentSkeleton.GetFrom("player")
  skeleton:WalkTo(-61.6, -40, 57.5)
end

function interactWith()
end

function destroy()
end