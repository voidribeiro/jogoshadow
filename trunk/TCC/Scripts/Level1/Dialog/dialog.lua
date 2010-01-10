function start()
	print("Starting dialog script")
end

function update()
  --Binds the object to use its functions
  --local gameObj = GameObject.ReBinder(parentObject)
  local component = ComponentDialog.GetFrom("plano")
--  print (component)
  if component:IsButtonPressed("b1") > 0 then
  	-- print("Apertou")
  	-- print(component:IsButtonPressed("b1"))

    component:Say("Era uma vez um outro texto de dialogo, blah blah blah!!!")

  end
end

function destroy()
end