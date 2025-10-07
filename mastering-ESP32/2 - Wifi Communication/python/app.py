from fastapi import FastAPI
import uvicorn

# Constants
DATA_QUEUE_SIZE_LIMIT:int = 100
HOST_IP:str = "0.0.0.0"
PORT:int = 8000

app = FastAPI()

temperature_data:dict[str, list[float]] = dict()

@app.get("/")
def root():
    return {"Server Status" : "Running"}


@app.post("/temperature")
def receive_temperature(room_num:str, temperature_c:float):
    """
    Receives temperature data from ESP32 over HTTP request
    Args:
        room_num: the id of the room
        temperature_c: the temperature of the room
    """

    print(f"Received temperature data from {room_num}, {temperature_c} Celsius")

    # Append data to room, limiting length
    if room_num not in temperature_data:
        temperature_data[room_num] = list()
    temperature_data[room_num].append(temperature_c)
    if len(temperature_data[room_num]) > DATA_QUEUE_SIZE_LIMIT:
        temperature_data[room_num].pop(0)

    return {"Status", "Received"}

if __name__ == '__main__':
    print(f"Starting server at http://{HOST_IP}:{PORT}")
    uvicorn.run(app, host=HOST_IP, port=PORT)
