import requests
import sys
import json

def makerequest(city):
    url = f"https://geocoding-api.open-meteo.com/v1/search?name={city}"
    data = requests.get(url).json()

    if "results" not in data:
        print(json.dumps({"error": "city not found"}))
        sys.exit(1)

    lat = data["results"][0]["latitude"]
    lon = data["results"][0]["longitude"]

    weather_url = (
        f"https://api.open-meteo.com/v1/forecast?"
        f"latitude={lat}&longitude={lon}&current_weather=true"
    )

    weather_data = requests.get(weather_url).json()

    result = {
        "city": city,
        "weather": weather_data["current_weather"]
    }

    print(json.dumps(result))

if __name__ == "__main__":
    city = sys.argv[1]
    makerequest(city)
