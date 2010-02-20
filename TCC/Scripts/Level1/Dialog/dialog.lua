function start()
	print("Starting dialog script")
end

function update()
  --Binds the object to use its functions
  --local gameObj = GameObject.ReBinder(parentObject)
  local component = ComponentDialog.GetFrom("dialogo")
--  print (component)

  if component:IsButtonPressed("b1") > 0 then
     component:Say("Era uma vez um outro texto de dialogo, blah blah blah!!!")
  end

  if component:IsButtonPressed("b2") > 0 then
    component:Say("Vc clicou no botão 2, que eh uma imagem")
  end  

  if component:IsButtonPressed("b3") > 0 then
    Game.LoadLevel("Level2");
  end

end

function destroy()
end