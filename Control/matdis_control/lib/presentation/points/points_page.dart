import 'package:matdis_control/application/points/points_bloc.dart';
import 'package:matdis_control/presentation/points/points_big_icon_message.dart';
import 'package:matdis_control/presentation/points/widgets/custom_points_field_arranged.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

class PointsPage extends StatelessWidget {
  const PointsPage({super.key});

  @override
  Widget build(BuildContext context) {
    final pointsBlock = PointsBloc();
    final themeData = Theme.of(context);
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Text(
          "Matdis Control",
          style: themeData.textTheme.displayLarge,
        ),
      ),
      body: Center(
        child: Padding(
            padding: const EdgeInsets.symmetric(horizontal: 10),
            child: BlocBuilder<PointsBloc, PointsState>(
              bloc: pointsBlock,
              builder: (context, state) {
                if (state is PointsInitial) {
                  // return const PointsBigIconMessage(
                  //   message:
                  //       "Not connected to device!\nPlease connect to device and\ntry again!",
                  //   messageIcon: Icons.bluetooth_disabled,
                  // );
                  return Stack(clipBehavior: Clip.none, children: const [
                    CustomPointsFieldArranged(),
                  ]);
                } else if (state is PointsStateLoading) {
                  return const Center(child: CircularProgressIndicator());
                } else if (state is PointsStateLoaded) {
                  return Stack(clipBehavior: Clip.none, children: const [
                    CustomPointsFieldArranged(),
                  ]);
                } else if (state is PointsStateError) {
                  return const PointsBigIconMessage(
                    message:
                        "There is some error!\nPlease ask your Administrator for help.",
                  );
                }
                return const Placeholder();
              },
            )

            // const PointsBigIconMessage(
            //   message:
            //       "There is some error!\nPlease ask your Administrator for help.",
            // ),
            ),
      ),
    );
  }
}
