from request_process import *


async def handle_client(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    while True:
        try:
            header = await reader.readexactly(4)
            if not header:
                print("Client disconnected!")
                break
        except Exception as e:
            print("Client disconnected: ", e)
            break
        buf_size = int.from_bytes(header, 'little')
        buf = await reader.readexactly(buf_size)
        request = RequestData.from_bytes(buf)
        response_bytes = request_process(request).to_bytes()

        if len(response_bytes) > 0:
            packet = Packet(len(response_bytes) + 1, bytes([request.req_type.value]) + response_bytes)
            writer.write(packet.to_bytes())
            await writer.drain()

    writer.close()


async def main():
    server = await asyncio.start_server(
        handle_client, '127.0.0.1', 8888)

    addr = server.sockets[0].getsockname()
    print(f'Serving on {addr}')

    async with server:
        await server.serve_forever()


asyncio.run(main())
