import 'dart:convert';

import 'package:matdis_control/domain/entities/advicer_entity.dart';
import 'package:matdis_control/infrastructure/exceptions/exceptions.dart';
import 'package:matdis_control/infrastructure/models/advice_model.dart';
// import 'package:http/http.dart' as http;
import 'package:http/http.dart';

abstract class AdviceRemoteDatasource {
  ///requests a random advice from free api
  ///throws a server exception if respond code is not 200
  Future<AdviceEntity> getRandomAdviceFromApi();
}

class AdviceRemoteDatasourceImplementation implements AdviceRemoteDatasource {
  final Client client;

  AdviceRemoteDatasourceImplementation({required this.client});
  @override
  Future<AdviceEntity> getRandomAdviceFromApi() async {
    final response = await client.get(
        Uri.parse("https://api.adviceslip.com/advice"),
        headers: {"Content-Type": "application/json"});
    if (response.statusCode != 200) {
      throw ServerException();
    }
    final responseBody = jsonDecode(response.body);
    return AdviceModel.fromJson(responseBody["slip"]);
  }
}
