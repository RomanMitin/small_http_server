# Start via `make test-debug` or `make test-release`
async def test_basic(service_client):
    response = await service_client.post('/post', params={'name': 'Tester'})
    assert response.status == 200
    response = await service_client.get('/get', params={'name': 'Tester'})
    assert response.status == 200
