import 'package:matdis_control/domain/failures/failures.dart';
import 'package:matdis_control/domain/entities/advicer_entity.dart';
import 'package:matdis_control/domain/repositories/advicer_repository.dart';
import 'package:matdis_control/infrastructure/datasources/advicer_remote_datasource.dart';
import 'package:matdis_control/infrastructure/exceptions/exceptions.dart';
import 'package:dartz/dartz.dart';

class AdvicerRepositoryImplementation implements AdvicerRepository {
  final AdviceRemoteDatasource adviceRemoteDatasource;

  AdvicerRepositoryImplementation({required this.adviceRemoteDatasource});

  @override
  Future<Either<Failure, AdviceEntity>> getAdviceFromApi() async {
    try {
      final remoteAdvice =
          await adviceRemoteDatasource.getRandomAdviceFromApi();
      return Right(remoteAdvice);
    } catch (e) {
      if (e is ServerException) {
        return Left(ServerFailure());
      }
      return Left(GeneralFailure());
    }
  }
}
