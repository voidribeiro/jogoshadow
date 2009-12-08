local splashTime = 5000

function startScript()
  print("Loading Start.")
  local gameObject = GameObject.Instantiate("Logo")
  gameObject:SetPosition(278.5,150,0)
  --Load Splash Image
  local component = ComponentImage.Instantiate(path .. "resources\\splash\\lucasarts_logo.jpg")
  component:AddTo(gameObject)
  
  local component = ComponentDialog.Instantiate()
  
  --component:SetPlayerImage()
  --component:SetNpcImage()
  --component:Visible()
  
  component:Say(path .. "resources\\hero\\hero.png", "Esta eh uma fala teste!", path .. "resources\\font\\fontlucida.png")
  component:AddTo(gameObject)
  
  --Set a Timer Function
  local component = ComponentTimer.Instantiate(splashTime, path .. "Scripts\\Start\\loader.lua","onTimeOut")
  component:AddTo(gameObject)
end

function onTimeOut()
  print("It should not get here before call timeout")
	local game = Game.GetInstance()
	game:LoadLevel("Level2");
end