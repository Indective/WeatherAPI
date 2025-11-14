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
        f"latitude={lat}&longitude={lon}"
        f"&current=temperature_2m,relative_humidity_2m,precipitation,rain,pressure_msl,wind_speed_10m,"
        f"wind_direction_10m,cloud_cover,visibility,weather_code"
    )

    weather_data = requests.get(weather_url).json()

    result = {
        "city": city,
        "weather": weather_data["current"]
    }

    print(json.dumps(result))

if __name__ == "__main__":
    city = sys.argv[1]
    makerequest(city)
