import 'package:matdis_control/domain/entities/advicer_entity.dart';
import 'package:equatable/equatable.dart';

class AdviceModel extends AdviceEntity with EquatableMixin {
  AdviceModel({required super.advice, required super.id});

  factory AdviceModel.fromJson(Map<String, dynamic> parsedJson) {
    return AdviceModel(
        advice: parsedJson["advice"] as String, id: parsedJson["id"] as int);
  }

  @override
  List<Object?> get props => [advice, id];
}
