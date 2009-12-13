local splashTime = 10000

function startScript()
  print("Loading Start.")
  local gameObject = GameObject.Instantiate("Logo")
  gameObject:SetPosition(278.5,150,0)
  --Load Splash Image
  local component = ComponentImage.Instantiate(path .. "resources\\splash\\lucasarts_logo.jpg")
  component:AddTo(gameObject)
  
  local component = ComponentDialog.Instantiate()

  component:Say( " Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate.")
  component:SetPlayerImage(path .. "resources\\hero\\hero.png")
  component:SetNpcImage(path .. "resources\\hero\\hero.png")
  component:SetFont(path .. "resources\\font\\fontlucida.png")

  component:AddTo(gameObject)
  
  --Set a Timer Function
  local component = ComponentTimer.Instantiate(splashTime, path .. "Scripts\\Start\\loader.lua","onTimeOut")
  component:AddTo(gameObject)
  
  local component = ComponentTimer.Instantiate(5000, path .. "Scripts\\Start\\loader.lua","sayOther")
  component:AddTo(gameObject)

end

function onTimeOut()
  print("It should not get here before call timeout")
	local game = Game.GetInstance()
	game:LoadLevel("Level2");
end

function sayOther()

  local component = ComponentDialog.GetFrom("Logo")
  component:Say("Era uma vez um outro texto de dialogo, blah blah blah!!!")
  --component:SetVisible(false)

end
