local splashTime = 3000

function startScript()
  print("Loading Start.")
  --Just for reference
  --local gameObject = GameObject.InstPersistent("Logo")
  local gameObject = GameObject.Instantiate("Logo")
  gameObject:SetPosition(278.5,150,0)
  --Load Splash Image
  local component = ComponentImage.Instantiate(path .. "resources\\splash\\lucasarts_logo.jpg")
  component:AddTo(gameObject)
  
  --Set a Timer Function
  local gameObject = GameObject.Instantiate("Timer")
  local component = ComponentTimer.Instantiate(splashTime, path .. "Scripts\\Start\\loader.lua","onTimeOut")
  component:AddTo(gameObject)

end

function onTimeOut()
  print("It should not get here before call timeout")
	local game = Game.GetInstance()
	game:LoadLevel("Level1");
end

