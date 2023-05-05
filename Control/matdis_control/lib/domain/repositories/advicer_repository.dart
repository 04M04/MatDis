import 'package:matdis_control/domain/entities/advicer_entity.dart';
import 'package:matdis_control/domain/failures/failures.dart';
import 'package:dartz/dartz.dart';

abstract class AdvicerRepository {
  Future<Either<Failure, AdviceEntity>> getAdviceFromApi();
}
