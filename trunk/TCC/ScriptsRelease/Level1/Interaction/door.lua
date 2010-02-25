function start()
	print("Starting inventory manager")
end

function update()
end

function interact()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:Say("A porta esta trancada.")
end

local speachCounter = 0

function inspect()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  dialog:ClearOptions()

  if (speachCounter < 1) then
    dialog:Say("A porta de saida.")
  else
    if (speachCounter < 2) then
      dialog:Say("Nao vou conseguir passar pela porta sem abri-la")
    else
      if (speachCounter < 3) then
        dialog:Say("Posso passar o dia todo olhando para porta se quiser.")
      else
        dialog:Say("Deixa eu pensar. Onde coloquei a chave mesmo?")
      end
    end
  end
  speachCounter = speachCounter + 1
end

function walk()
  local selector = ComponentSelector.GetFrom(parentObject)
  local skeleton = ComponentSkeleton.GetFrom("player")
  skeleton:WalkTo(90.38, -40, -3.67)
end

local numberOfTries = 0

function interactWith()
  walk()
  local dialog = ComponentDialog.GetFrom("dialogo")
  if (interactionObject == "chave") then
    if (numberOfTries < 2) then
      dialog:Say("A chave nao abre a porta. Falta implementar.")
      numberOfTries = numberOfTries + 1
    else
      dialog:Say("Era so insistir um pouco. Agora nao a nada que me impessa de sair daqui.")
    end
  else
    dialog:Say("E o que acha que eu devia fazer com isso?")
  end
end

function destroy()
end