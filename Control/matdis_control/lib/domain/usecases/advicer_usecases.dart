import 'package:matdis_control/domain/entities/advicer_entity.dart';
import 'package:matdis_control/domain/failures/failures.dart';
import 'package:matdis_control/domain/repositories/advicer_repository.dart';
import 'package:dartz/dartz.dart';

class AdvicerUsecases {
  final AdvicerRepository adviceRepository;
  AdvicerUsecases({required this.adviceRepository});
  Future<Either<Failure, AdviceEntity>> getAdviceUsecase() async {
    //call function from repo to get advice
    return adviceRepository.getAdviceFromApi();
    //Business logic implementieren z.B. rechnungen etc.
  }
}
